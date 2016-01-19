#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "len_prefix.h"
#include "shared.h"
#include "server.h"

int running = 1;

int main() {
  int socket_id, client, e;
  char resp[10];

  socket_id = setup_server(PORT);
  if (socket_id < 0) {
    perror("Error setting up server");
    exit(-1);
  }

  printf("<server> listening on %d\n", PORT);

  client = accept(socket_id, NULL, NULL); // blocks here on connection

  printf("<server> connected: %d\n", client);

  while (running) {
    e = handle_request(client);
    if (e < 0) {
      running = 0;
    }
  }

  close(client);
  close(socket_id);
}

int setup_server(int port) {
  int socket_id, e;

  socket_id = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_id < 0) return socket_id;

  struct sockaddr_in listener = {
    .sin_family = AF_INET,   // socket type IPv4
    .sin_port = htons(port), // port #
    .sin_addr.s_addr = INADDR_ANY
  };

  e = bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  if (e < 0) return e;

  e = listen(socket_id, 1);
  if (e < 0) return e;

  return socket_id;
}

int handle_request(int socket) {
  int read_bytes, e;
  char * message = NULL;

  read_bytes = len_prefix_read(socket, (void **)&message);
  if (read_bytes < 0) return read_bytes;

  printf("client[%d]: %s", socket, message);

  char * resp = "RECEIVED";

  e = len_prefix_write(socket, resp, strlen(resp));

  free(message);

  return e;
}
