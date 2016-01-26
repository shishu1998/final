#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <signal.h>
#include "message.h"
#include "shared.h"
#include "server.h"

int running = 1;

static void sighandler(int signo) {
  if (signo == SIGINT) {
    running = 0;
  }
}

int main() {
  int listening_socket, client_socket, e;

  struct sigaction action = {
    .sa_handler = sighandler,
    .sa_flags = 0
  };
  sigemptyset(&action.sa_mask);

  sigaction(SIGINT, &action, NULL);

  int listener = 1;

  listening_socket = setup_server(PORT);
  if (listening_socket < 0) {
    perror("Error setting up server");
    exit(-1);
  }

  struct user client;

  while (running) {
    if (listener) {
      printf("<server> listening on %d\n", PORT);
      client_socket = accept(listening_socket, NULL, NULL); // blocks here on connection
      e = handshake(client_socket, &client);
      printf("<server> connected: %s\n", client.name);
      listener = fork();
      if (listener) {
        close(client_socket);
      } else {
        close(listening_socket);
      }
    } else {
      e = handle_request(client_socket);
      if (e <= 0) {
        running = 0;
      }
    }
  }

  if (listener) {
    close(listening_socket);
  } else {
    close(client_socket);
  }

  return 0;
}

int setup_server(int port) {
  int listening_socket, e;

  listening_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (listening_socket < 0) return listening_socket;

  struct sockaddr_in listener = {
    .sin_family = AF_INET,   // socket type IPv4
    .sin_port = htons(port), // port #
    .sin_addr.s_addr = INADDR_ANY
  };

  e = bind(listening_socket, (struct sockaddr *)&listener, sizeof(listener));
  if (e < 0) return e;

  e = listen(listening_socket, 1);
  if (e < 0) return e;

  return listening_socket;
}

int handle_request(int socket_id) {
  int e;
  struct signal sig;

  e = read(socket_id, &sig, sizeof(sig));
  if (e < 0) return -1;

  switch (sig.type) {
  case DISCONNECT:
    running = 0;
    break;
  case MESSAGE:
    printf("<%s>: %s\n", sig.body.message.from.name, sig.body.message.text);
    struct signal resp = new_message_sig(sig.body.message.to, sig.body.message.from, "RECEIVED!");
    e = write(socket_id, &resp, sizeof(resp));
    if (e < 0) return -1;
    break;
  }

  return e;
}

int handshake(int client_socket, struct user *client) {
  int e;
  struct signal sig;
  e = read(client_socket, &sig, sizeof(sig));
  if (e <= 0) return -1;

  e = write(client_socket, &sig, sizeof(sig));
  if (e <= 0) return -1;

  *client = sig.body.handshake;

  return 0;
}
