
#include <arpa/inet.h>
#include <ncurses.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {

  char buffer[256];
  int i;
  int errno;
  int socket_id, connect_response, c;

  /* initscr(); */
  /* noecho(); */
  /* keypad(stdscr, TRUE); */
  /* nodelay(stdscr, TRUE); */

  // create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );

  // bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(5000);
  //Set the IP address to connect to
  //127.0.0.1 is the "loopback" address of any machine
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));

  //attempt a connection
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  if (i == -1) {
    printf("Error connecting to server: %s", strerror(errno));
  }
  printf("<client> connect returned: %d\n", i);
  
  while (1) {

    errno = recv( socket_id, buffer, sizeof(buffer), 0);
    printf("Error: %s\n", strerror(errno));
    printf("Received: %s\n", buffer);
    printf("Enter A Message\n");
    fgets(buffer, 256, stdin);
    send( socket_id, buffer, sizeof(buffer), 0);
  }

  /* while (1) { */
  /*   c = getch(); */
  /*   if (c != -1) { */
  /*     sprintf(buffer, "%d", c); */
  /*     printw("%s", buffer); */
  /*   } */
  /* } */

  return 0;
}
