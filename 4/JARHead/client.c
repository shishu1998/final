
#include <arpa/inet.h>
#include <ncurses.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main() {
 
  int fd[2];
  char input_buffer[8];
  char write_buffer[256];
  char read_buffer[256];
  char server_buffer[256];
  int i, c, errno, input_writer, input_reader;
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
  i = connect(socket_id, (struct sockaddr *) &socket_info, sizeof(socket_info));
  if (i == -1) {
    printf("Error connecting to server: %s", strerror(errno));
    return 0;
  }

  // Make an unnamed pipe for char input transfer.
  pipe(fd);
  
  // The child process will constantly pipe the user input to the parent
  // process.
  switch (fork()) {
  case -1:
    printf("Something broke!\n");
    return 0;
  
  case 0:
    // Child process - Constantly sends user input to the parent process.
    initscr();
    noecho();

    close(fd[READ]);
    while (c = getch()) {
      sprintf(input_buffer, "%d", c);
      write(fd[WRITE], input_buffer, sizeof(input_buffer));
    }
    endwin();
    break;

  default:
    // Parent process - Takes the user input and sends it to the server while
    // redrawing the screen at the same time. This forking is necessary because
    // otherwise, the loop will hang while we wait for user input.
    initscr();
    noecho();
    close(fd[WRITE]);

    while (1) {      
      read(fd[READ], read_buffer, sizeof(read_buffer));
      send(socket_id, read_buffer, sizeof(read_buffer), 0);

      errno = recv(socket_id, server_buffer, sizeof(server_buffer), 0);
      printw("%s", server_buffer);
      refresh();
      usleep(10000);
      clear();
    }
    close(socket_id);
    endwin();
    break;
  }
  
  return 0;
}
