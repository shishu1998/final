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

int old_bid = 0; //simple initialization value

/*
	CODE ADAPTED FROM http://www.linuxhowtos.org/C_C++/socket.htm
*/

// NOTE: Move the write-conditional-part back into writing.h

int paddles[5]; //currently allow only 5 bidders at a time
int num_paddles;
//char *bidfile = "curr_bid.txt";

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

	num_paddles = 0;
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
			dostuff(newsockfd);
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
 once a connnection has been established.
 *****************************************/
void dostuff (int sock)
{
	int n;
	char buffer[256];
	  
	bzero(buffer,256);
	n = read(sock,buffer,255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);
	n = write(sock,"New bid:",18);
	if (n < 0) error("ERROR writing to socket");
	else write_bid(buffer);
}

void write_bid(char *offer) {
	int status;
	int fd;
//	char old_bid[256]; // should be ample space
//	read(fd, old_bid, sizeof(old_bid));
	printf("(SS: ensuring atoi works) %d, %d\n", atoi(offer), old_bid);
	if (atoi(offer) > old_bid) {
		old_bid = atoi(offer);
		printf("SS: trying to input bid...\n");
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
				printf("removes shared memory\n");
				execvp(remv[0], remv);
				exit(0);
			} else {
				wait(&status);
			}
		} else {
			wait(&status);
		} 
	} else {
		printf("\nSS: You have already been outbid.\n");
		close(fd);
	}
}
