#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include "players.c"

void sendpos( int fd ) {
  char *buffer;
  buffer = "init";
  int n = write(fd, buffer, sizeof(buffer) );
}

char randColor( int p ) {
  char color;
  if ( p == 0 ) 
    color = 'r';
  else if ( p == 1 )
    color = 'b';
  else if ( p == 2 )
    color = 'g';
  else if ( p == 3 )
    color = 'y';
  else 
    printf( "Error in handling colors\n" );
  return color;
}

card * generateHand() {
  card cards[1000];
  int i = 0;
  while ( i < 7 ) {
    cards[i].value=rand()%10;
    cards[i].color=randColor( rand()%4 ); 
  }
  
}

void doprocessing (int sock) {

  sleep(1);
  printf("one (w)\n");
  int p = write(4, "go", sizeof("go"));
  sleep(1); //GO TO SLEEP and wait for read to happen first
  if (p < 0) {
    perror("ERROR writing");
    printf("error: %s \n", strerror(errno));
    exit(1);
  }
   
	   
  
  int n;
  char buffer[256];
  bzero(buffer,256);
  printf("two (r)\n");
  n = read(sock,buffer,255);
  printf("able to get pass two\n");

  if (n < 0) {
    perror("ERROR reading from socket");
    exit(1);
  }
   
  printf("Here is the message: %s\n",buffer);
  printf("three (w)\n");
  n = write(sock,"I got your message",18);
   
  if (n < 0) {
    perror("ERROR writing to socket");
    exit(1);
  }
	
}

int main( int argc, char *argv[] ) {
  
  ask_for_total();
  int turns;
  
  int sockfd, newsockfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n, pid;
   
  /* First call to socket() function */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }
   
  /* Initialize socket structure */
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = 5001;
   
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  
  /* Now bind the host address using bind() call.*/
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("ERROR on binding");
    exit(1);
  }

  /* Now start listening for the clients, here
   * process will go in sleep mode and will wait
   * for the incoming connection
   */
   
  listen(sockfd,5);
  clilen = sizeof(cli_addr);
   
  while (1) {
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    
    //if ( newsockfd == 4 ) 
    //  sendpos( 4 );
    
    players_connect();
    player_ids[player_count-1] = newsockfd;
    int i=0;
    while(i<player_count){
      printf("player_ids[%d] = %d\n", i, player_ids[i]);
      i++;
    }
		
    if (newsockfd < 0) {
      perror("ERROR on accept");
      exit(1);
    }
      
    /* Create child process */
    pid = fork();
		
    if (pid < 0) {
      perror("ERROR on fork");
      exit(1);
    }
      
    if (pid == 0) {
      while( 1 ) {		
	/* This is the client process */
	printf("hello\n");
	//close(sockfd);
	doprocessing(newsockfd);
      }
    }
    else {
      //close(newsockfd);
    }
		
  } /* end of while */
}
