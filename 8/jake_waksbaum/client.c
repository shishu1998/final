#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "len_prefix.h"
#include "shared.h"
#include "client.h"

int running = 1;

int main() {
  int socket_id, e;

  socket_id = connect_to_server(IP, PORT);

  while (running) {
    int bytes_read;
    char input[256];
    printf("> ");
    fflush(stdout);

    e = bytes_read = read(STDIN_FILENO, input, sizeof(input)-1);
    check_errors_except("Error reading input", e, EINTR);
    input[bytes_read++] = '\0';

    if (!running) {
      continue; // we usually C-c during input
    } else if (is_exit(input)) {
      running = 0;
      continue;
    }

    e = send_request(input, bytes_read, socket_id);
    check_errors("Error sending request", e);

    e = handle_response(socket_id);
    check_errors("Error handling response", e);
  }
  close(socket_id);
}

int connect_to_server(char * ip, int port) {
  int socket_id, e;

  // create socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  // bind to port/address
  struct sockaddr_in sock = {
    .sin_family = AF_INET,
    .sin_port = htons(port)
  };
  inet_aton(ip, &(sock.sin_addr) );

  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));

  // attempt a connection
  e = connect(socket_id, (struct sockaddr*)&sock, sizeof(sock));
  if (e < 0) return e;

  return socket_id;
}

int is_exit(char *input) {
  return strcmp(input, "exit\n") == 0;
}

int send_request(char *req, size_t len, int socket_id) {
  return len_prefix_write(socket_id, req, len);
}

int handle_response(int socket_id) {
  int e;
  char * buf = NULL;

  e = len_prefix_read(socket_id, (void **)&buf);
  if (e < 0) return e;

  printf("server: %s\n", buf);

  free(buf);

  return e;
}
