<<<<<<< HEAD
=======
/**
 * Client code.
 */
>>>>>>> f77fcc45a5b5d702d0a2e4f4875a235af0fcc1ac

#include <arpa/inet.h>
#include <ncurses.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

<<<<<<< HEAD
#define READ 0
#define WRITE 1

int main() {
 
  int fd[2];
  char input_buffer[8];
  char write_buffer[256];
  char read_buffer[256];
  char server_buffer[256];
=======
#define INPUT_SEND_DELAY_MICROSECONDS 30000
#define SCREEN_REFRESH_DELAY_MICROSECONDS 10000

int main() {

  // Variable initialization.
  char buffer[4096];
>>>>>>> f77fcc45a5b5d702d0a2e4f4875a235af0fcc1ac
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
  
  // Receives and stores a UID which all further communications will be
  // tagged with.
  char uid[8];
  recv(socket_id, uid, sizeof(uid), 0);

  // The child process constantly sends user input to the server.
  switch (fork()) {
  case -1:
    printf("Failed to fork!\n");
    return 0;
  
  case 0:
    // Child process - Constantly sends user input to the server.
    initscr();
    noecho();
    nodelay(stdscr, TRUE);

    while (1) {
      // Read user input on the keyboard. nodelay() makes this a non-blocking
      // call, but we must use usleep() to make sure this loop doesn't run too
      // many times per second or user input will not be picked up.
      c = getch();
      // Format the received user input keycode with the stored UID.
      if (c != -1) {
        sprintf(buffer, "%s:%d", uid, c);
      } else {
        sprintf(buffer, "%s: ", uid);
      }
      // Send the user input and stored UID to the server.
      send(socket_id, buffer, sizeof(buffer), 0);
      usleep(INPUT_SEND_DELAY_MICROSECONDS);
    }
    endwin();
    break;

<<<<<<< HEAD
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
      usleep(5000);
      clear();
    }
=======
  default:
    // Parent process - Constantly receives the server's data which contains
    // the state of the game and writes it to the screen.
    initscr();
    noecho();

    while (1) {
      // Constantly receive the state of the map from the server.
      recv(socket_id, buffer, sizeof(buffer), 0);
      display_printw(buffer);
      refresh();
      usleep(SCREEN_REFRESH_DELAY_MICROSECONDS);
      clear();
    }

>>>>>>> f77fcc45a5b5d702d0a2e4f4875a235af0fcc1ac
    close(socket_id);
    endwin();
    break;
  }
  
  return 0;
}
