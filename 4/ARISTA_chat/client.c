#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "connection.h"

int connect_server(char *hostname) {
	int socket_id;
	char ip[256];
	int i;
	
    //create the socket
    socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
    //bind to port/address
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;   
    sock.sin_port = htons(PORT);
    //Set the IP address to connect to
	struct in_addr *addr;
	struct hostent *h = (void *)123456789;
	h = gethostbyname(hostname);
	printf("%s\n", hostname);
	if (h == NULL) {
		printf("ERROR - cannot find hostname.\n");
		//127.0.0.1 is the "loopback" address of any machine
		inet_aton( "127.0.0.1", &(sock.sin_addr) );
		return -1;
	}
	addr = (struct in_addr *) h->h_addr;
	inet_ntoa(*addr);
	sock.sin_addr = *addr;
    bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));
  
    //attempt a connection
    i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
	
	return socket_id;
}

static void sighandler(int signo) {
	if (signo == SIGINT) {
		printf("Goodbye!\n");
		exit(0);
	}
}

int main(int argc, char **argv) {
  signal(SIGINT, sighandler);

  int socket_id;
  char *hostname;
  char buffer[256];
  
  if (argc < 2) {
      printf("Usage: client <hostname>\n");
      exit(1);
  } else {
      hostname = argv[1];
  }
    
  socket_id = connect_server(hostname);
  printf("<client> connect returned: %d\n", socket_id);
	
  int type = -1;  // 0 (tutor) or 1 (tutee) - get this from login
  type = (int)argv[2][0] - 48;  // convert from ASCII value
  // send type to server
  write(socket_id, &type, sizeof(type));
  /**
  int subj;
  subj = (int)argv[3][0] - 48;
  */

  while(socket_id >= 0){

    printf("<client> waiting\n");
    char s[100];
    sleep(1);
    read(socket_id, s, sizeof(s));
    printf("<client> received: %s\n", s);
    printf("You: ");
    fgets(s, sizeof(s), stdin);
	if (strcmp(s, "exit\n") == 0) {
		printf("Goodbye\n");
		close(socket_id);
		exit(0);
	}
    write(socket_id, s, sizeof(s));

  }

  return 0;
}
