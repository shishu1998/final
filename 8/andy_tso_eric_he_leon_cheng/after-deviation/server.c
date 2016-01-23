#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include "players.c"

void doprocessing (int sock) {

  //printf("current_position: %d\n", current_position);
  //printf("desired_total: %d\n", desired_total);

  /* if (current_position == desired_total){ */
  /*   current_position = 0; */
  /* } */

  //printf("sock: %d\n", sock);  
  //printf("player_ids[current_position]: %d\n", player_ids[current_position]);  
  //printf("one (w)\n");
  //if (sock==player_ids[current_position]){
  sleep(1); //GO TO SLEEP and wait for read to happen first    
  int p = write(sock, "go", sizeof("go"));
  
  if (p < 0) {
    perror("ERROR writing");
    printf("error: %s \n", strerror(errno));
    exit(1);
  }
  //}	
  
    
  int n;
  char buffer[256];
  bzero(buffer,256);
  //printf("two (r)\n");
  n = read(sock,buffer,255);
  //printf("able to get pass two\n");
  
  
  if (n < 0) {
    perror("ERROR reading from socket");
    exit(1);
  }
  
  printf("Here is the message: %s\n",buffer);
  //printf("three (w)\n");
  n = write(sock,"I got your message",18);
  
  //current_position++;
  
  if (n < 0) {
    perror("ERROR writing to socket");
    exit(1);
  }
  
  //printf("current_position: %d\n", current_position);
  //printf("desired_total: %d\n", desired_total);
  
  
}

int main( int argc, char *argv[] ) {
  
  srand(time(NULL));
  
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
  
  printf("player_count: %d\n", player_count);
  printf("desired_total: %d\n", desired_total);
  
  while (1) {
    if(player_count <= desired_total){
      
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
            
      /* if ( pid > 0 ){ */
      /* 	child_ids[player_count-2] = pid; */
      /* 	int i2=0; */
      /* 	while(i2<player_count){ */
      /* 	  printf("child_ids[%d] = %d\n", i, child_ids[i]); */
      /* 	  i2++; */
      /* 	} */
      /* 	//printf("getpid: %d\n", getpid()); */
      /* 	printf("pid: %d\n", pid); */
	
      /* 	if (pid < 0) { */
      /* 	  perror("ERROR on fork"); */
      /* 	  exit(1); */
      /* 	} */
      /* } */

      if (pid == 0) {
	
	
	while( 1 ) {		
	  /* This is the client process */
	  printf("hello\n");
	  //close(sockfd);
	  doprocessing(newsockfd);

	  /* printf("current_position: %d\n", current_position); */
	  /* printf("desired_total: %d\n", desired_total); */
	  /* printf("player_ids[current_position]: %d\n", player_ids[current_position]); */
	  /* int i=0; */
	  /* while(i<player_count){ */
	  /*   printf("player_ids[%d] = %d\n", i, player_ids[i]); */
	  /*   i++; */
	  /* } */
	  /* printf("current_position: %d\n", current_position); */
	  /* printf("newsockfd: %d\n", newsockfd); */
	  //sleep(1);
	  
	}

      }
    }
    else {
      /* Close the client if desired_total num of players aleady connected */
      write(newsockfd, "terminate", sizeof("terminate"));
      close(newsockfd);
      if (pid==0){
	close(sockfd);
      }
    }
		
  } /* end of while */

}
