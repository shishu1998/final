#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "players.c"

player p;

static void sighandler(int signo) {
  if (signo == SIGINT) {
    printf("ctrl-c was pressed\n");
    exit(0);
  }
}

int main(int argc, char *argv[]) {

  p = generate_hand(p);
  printf("p.num_cards: %d\n", p.num_cards);
  //player_action(p);
  
  signal(SIGINT, sighandler);

  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
   
  char buffer[256];
   
  if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
  }
	
  portno = atoi(argv[2]);
  /* Create a socket point */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }
	
  server = gethostbyname(argv[1]);
   
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
   
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
   
  /* Now connect to the server */
  if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("ERROR connecting");
    exit(1);
  }

  while (1) {
    
    player_action(p);

    /* Now ask for a message from the user, this message
     * will be read by server
     */

    /* Server determines turn */
    char *buffer2;
    //printf("four (r)\n");
    int a = read(sockfd, buffer2, 255 );
    //printf ( "debug\n" );
    //printf("able to get pass four\n");
    if (a < 0) {
      perror("ERROR reading");
      printf("error: %s \n", strerror(errno));
      exit(1);
    }
      
    printf( "buffer2: %s\n", buffer2 );
    if ( !strcmp(buffer2, "terminate") ) {
      break;
    }

    if ( !strcmp(buffer2, "go") ) {
      printf("Please enter the message: ");
      bzero(buffer,256);
      fgets(buffer,255,stdin);

      char * scard1;
      char * scard2;
      int num = atoi(buffer);
      printf( "debugging\n");
      if (num==p.num_cards){
        printf( "debugging\n");
      	p.cards[p.num_cards] = draw_card();
      	p.num_cards++;
      	printf( "debugging\n");
      	p.num_cards++;
      	printf( "debugging\n");
      	scard1 = "draw";
      	scard2 = "draw";
      }
      else{
      	card c = p.cards[num];
      	int value = c.value;
      	int color = c.color;
      	char svalue[100];
      	sprintf(svalue, "%d", value);
      	char cvalue[100];
      	scard1 = svalue;
      	sprintf(cvalue, "%d", color);
      	scard2 = cvalue;
      	printf("tried to stringify a card in client: %s %s\n", scard2, scard1);
      	
      	card *write_card;
        printf( "Index:%d Color:%d Value:%d\n", num, p.cards[num].color, p.cards[num].value );
        *write_card = p.cards[num];
        printf("write_card: %d, %d\n", (*write_card).color, (*write_card).value);
        n = write(sockfd, write_card, sizeof(write_card));
        printf("Bytes written: %d\n", n);
        printf("error #%d: %s\n", errno, strerror(errno));
        printf("\n");
        p = remove_card(p, num);
      }

      /* Send message to the server */
      //printf("five (w)\n");
      //n = write(sockfd, buffer, strlen(buffer));

      
    
      
      if (n < 0) {
	perror("ERROR writing to socket");
	exit(1);
      }
      sleep(1);
    }  
   
    /* Now read server response */
    bzero(buffer,256);
    //printf("six (r)\n");
    n = read(sockfd, buffer, 255);
  
    if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
    }
	
    //printf("%s\n",buffer);
    //return 0;
  }
  
}
