#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include "old_main.h"

/*
	CODE ADAPTED FROM http://www.linuxhowtos.org/C_C++/socket.htm
*/

#define SIZEBUFF 256
char my_paddle[100];

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(int argc, char *argv[])
{
	memset(my_paddle, 0, sizeof(my_paddle));
	sprintf(my_paddle, "%d", getpid());
	printf("Your paddle number is: %s\n", my_paddle);
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[SIZEBUFF];
	if (argc < 3) {
	   fprintf(stderr,"usage %s hostname port\n", argv[0]);
	   exit(0);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
		 (char *)&serv_addr.sin_addr.s_addr,
		 server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
	
	while (1) {
		old_main();

		if (BID_MODE != 0) {
			n = write(sockfd, my_paddle, strlen(my_paddle)+1);

			memset(buffer, 0, sizeof(buffer)); // better than bzero
			printf("Your bid: ");
			bzero(buffer,SIZEBUFF);
			
			clean_stdin();
			fgets(buffer, sizeof(buffer)-1, stdin);

			n = write(sockfd,buffer,strlen(buffer));
			printf("buffer is %s\n", buffer);
			if (n < 0) 
				 error("ERROR writing to socket");
			bzero(buffer,SIZEBUFF);

			//check for errors
			if (errno) printf("error %d: %s\n", errno, strerror(errno));
		} else if (REQ_MODE != 0) {
			// request bid data from server
			n = write(sockfd, "2", 2); // I'm just taking 2 to mean REQ_MODE for server
			if (n < 0) error("ERROR writing to socket");

			printf("attempting a request at info, n = %d\n", n);
			printf("CURRENT BID AT: ");

			//check for errors
			if (errno) printf("error %d: %s\n", errno, strerror(errno));
		} else if (QUIT_MODE != 0) {
			// tell server that you've left
			n = write(sockfd, "3", 2); // taking 3 to be QUIT_MODE for server
			if (n < 0) error("ERROR writing to socket");

			printf("Notified server that you have quit.\n");

			//check for errors
			if (errno) printf("error %d: %s\n", errno, strerror(errno));

			exit(0);
		}

	//	memset(buffer, 0, sizeof(buffer));
		bzero(buffer,SIZEBUFF);

		n = read(sockfd,buffer,SIZEBUFF-1);
		if (n < 0) error("ERROR reading from socket");
		printf("%s\n", buffer);

	}
	close(sockfd);
	return 0;
}

