#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>

#include <errno.h>
#include <string.h>

// Code courtesy of http://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
int main() {

  int socketfd, clientconnfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  if (socketfd < 0) {
    perror("Error opening socket");
    exit(1);
  }

  memset(&serv_addr, 0, sizeof(serv_addr));

  portno = 5001;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(socketfd, &serv_addr, sizeof(serv_addr)) < 0) {
    perror("Error on binding");
    exit(1);
  }

  listen(socketfd, 5);
  clilen = sizeof(cli_addr);

  clientconnfd = accept(socketfd, &cli_addr, &clilen);

  if (clientconnfd < 0) {
    perror("Error connecting to a client");
    exit(1);
  }

  FILE *stream = fdopen(clientconnfd, "w");

  char *input = fgets(buffer, sizeof(buffer), stream);

  if (!input) {
    perror("Error reading from socket");
    exit(1);
  }

  printf("Here is the message: %s\n", buffer);

  if (fprintf(stream, "I got your message\n") < 0) {
    perror("Error sending response");
    exit(1);
  }
      
  return 0;
}
