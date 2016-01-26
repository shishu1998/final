#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#define READ 0
#define WRITE 1

static void clean_up_memory(int signo) {
}

int main() {
 
  int fd[2];
  char input_buffer[8];
  char write_buffer[256];
  char read_buffer[256];
  int c, input_writer, input_reader;

  // Make an unnamed pipe for char input transfer.
  pipe(fd);

  // create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );

  // bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(5000);
  // Set the IP address to connect to
  // 127.0.0.1 is the "loopback" address of any machine
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));

  //attempt a connection
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  if (i == -1) {
    printw("Error connecting to server: %s", strerror(errno));
    return 0;
  }
  printw("<client> connect returned: %d\n", i);

  // The child process will constantly pipe the user input to the parent
  // process.
  switch(fork()) {
  case -1:
    printf("Something broke!\n");
    return 0;
  
  case 0:
    // Child process - Constantly sends user input to the parent process.
    initscr();
    noecho();
    keypad(stdscr, TRUE);

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
    close(fd[WRITE]);

    while (1) {
      read(fd[READ], read_buffer, sizeof(read_buffer));
      send(socket_id, read_buffer, sizeof(read_buffer), 0);
      refresh();
    // errno = recv( socket_id, buffer, sizeof(buffer), 0);
    // printw("%w", buffer);
    // printf("Error: %s\n", strerror(errno));
    // printf("Received: %s\n", buffer);
    }
    endwin();
    break;
  }
  
  return 0;
}
