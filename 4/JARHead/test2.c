
#include <arpa/inet.h>
#include <ncurses.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

static void clean_up_memory(int signo) {
}

int main(int argc, char** argv) {

  char buffer[256];

  int i, c, errno;
  int socket_id;

  // Create a socket to send and receive data from the server.
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );

  // Bind to port/address.
  struct sockaddr_in socket_info;
  socket_info.sin_family = AF_INET;
  socket_info.sin_port = htons(5000);
  
  // Set the IP address to connect to.
  // 127.0.0.1 is the "loopback" address of any machine.
  inet_aton( "127.0.0.1", &(socket_info.sin_addr) );
  bind(socket_id, (struct sockaddr *) &socket_info, sizeof(socket_info));

  // Attempt to connect to the server.
  i = connect(socket_id, (struct sockaddr *)&socket_info, sizeof(socket_info));
  if (i == -1) {
    printf("Error connecting to server: %s", strerror(errno));
    return 0;
  }

  initscr();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  printw("hello");

  while (1) {
    c = getch();
    printw("%d", c);
    if (c != -1) {
      sprintf(buffer, "%d", c);
      printw("%s", buffer);
      send(socket_id, buffer, sizeof(buffer), 0);
    }
    errno = recv(socket_id, buffer, sizeof(buffer), 0);
    printw("%s", buffer);
    refresh();
  }

  return 0;
}
