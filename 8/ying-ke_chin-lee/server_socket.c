/* A simple server in the internet domain using TCP
	The port number is passed as an argument 
	This version runs forever, forking off a separate 
	process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include "writing.h"

/*
	CODE ADAPTED FROM http://www.linuxhowtos.org/C_C++/socket.htm
*/

#define SIZEBUFF 256

char *bidderfile = "bidders.txt";

int paddles[5]; //currently allow only 5 bidders at a time
int num_paddles;
//char *bidfile = "curr_bid.txt";

/* potential ending condition: all bidders leave */
int num_bidders = 0;
int auction_started = 0;

void dostuff(int); /* function prototype */
void write_bid(char *); // check if you can write the new bid, and then do the sem/shmem stuff
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

static void sighandler(int signo) {
	// get rid of the annoying mario
	if (signo == SIGINT) {
		printf("ctrl c was hit\n");
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sighandler);

	auction_started = 1;

	int sockfd, newsockfd, portno, pid;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			  sizeof(serv_addr)) < 0) 
			  error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	while (1) {
		newsockfd = accept(sockfd, 
				(struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) 
			error("ERROR on accept");
		pid = fork();
		if (pid < 0)
			error("ERROR on fork");
		if (pid == 0)  {
			close(sockfd);
			printf("\nA new user has connected to the auction.\n");
			num_bidders++;
			while (1) dostuff(newsockfd);
			exit(0);
		}
		else close(newsockfd);
	} /* end of while */
	close(sockfd);
	return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connection has been established.
 *****************************************/
void dostuff (int sock)
{
	int n;
	int has_msg = 0;
	char buffer[SIZEBUFF];
	char msg_out[SIZEBUFF]; //should be enough space...
	 
	bzero(buffer,SIZEBUFF);
	n = read(sock,buffer,SIZEBUFF-1);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);

	if (strcmp(buffer, "2") == 0) {		// next three lines newly added
		has_msg = 1;
		printf("in req info mode\n");
		// retrieve the necessary info
		
		// okay, this is yucky but is just the copy/paste of code from writing.h
		char last_bid[SIZEBUFF]; //hopefully enough space
		char new_char;
		int index = 0;

		FILE *fp;
		fp = fopen(bidfile, "r");
		fseek(fp, 0, SEEK_END);
		new_char = fgetc(fp);
		while (new_char != '\n') {
			last_bid[index] = new_char;
			index++;

			fseek(fp, -1*index, SEEK_END);
			new_char = fgetc(fp);
		}
		fclose(fp);
		last_bid[index] = '\0';
		printf("last_bid (backwards) is %s\n", last_bid);
	
		/* FLIP THE STRING AAAAACK *flips table* */
		reverse(last_bid);
		printf("last_bid (forwards?) is %s\n", last_bid);
//		strcpy(msg_out, last_bid);
		sprintf(msg_out, "%s", last_bid);

	} else if (strcmp(buffer, "3") == 0) {
		printf("in quit mode; a user has left the bidding\n");
		num_bidders--;
		printf("remaining bidders: %d\n", num_bidders);
		// here keep track of users still around, for end-of-auction condition.
	} else {
/*
	n = write(sock,"New bid:",18);
	if (n < 0) error("ERROR writing to socket");
	else write_bid(buffer);
*/
		//retrieve new bid
		bzero(buffer,SIZEBUFF);
		n = read(sock, buffer, SIZEBUFF-1); // works based on print statement
		printf("should contain new bid: %s\n", buffer);
		if (n < 0) error("ERROR reading from socket");

		write_bid(buffer);
		printf("success_write = %d\n", success_write);

		if (success_write) //strcpy(msg_out, "BID SUCCESSFUL.");
			sprintf(msg_out, "BID SUCCESSFUL.");
		else //strcpy(msg_out, "UNSUCCESSFUL: You have already been outbid.");
			sprintf(msg_out, "UNSUCCESSFUL: You have already been outbid.");
//		printf("length of msg_out is %d\n", strlen(msg_out));
		has_msg = 1;
	
	} //newly added, same goes for below
	printf("msg_out = %s\n", msg_out);
//	n = write(sock, msg_out, strlen(msg_out));
//	if (n < 0) error("SOME FORM OF ERROR OCCURED\n");
//	else if (has_msg) write(sock, msg_out, SIZEBUFF-1);
	if (has_msg) write(sock, msg_out, SIZEBUFF-1);

	bzero(msg_out, sizeof(msg_out));
}

void write_bid(char *offer) {
	int status;
	int fd;
	// now start writing.
	//open bid
	int f = fork();
	if (f == 0) {
		char *creat[3] = {"./control", "-c", NULL};
		int f0 = fork();
		if (f0 == 0) {
			execvp(creat[0], creat);
			exit(0);
		}
		else {
			wait(&status);
		}
		// write the bids
		file_write(offer);

		// close bid info
		char *remv[3] = {"./control", "-r", NULL};
		int f2 = fork();
		if (f2 == 0) {
			execvp(remv[0], remv);
			exit(0);
		} else {
			wait(&status);
		}
	} else {
		wait(&status);
	} 
}
