#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
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
      fflush(stdout);
      listener = fork();
      if (listener) {
        close(client_socket);
      } else {
        close(listening_socket);
      }
    } else {
      e = handle_request(client_socket, client);
      if (e < 0) {
        running = 0;
      }
    }
  }

  if (listener) {
    close(listening_socket);
  } else {
    remove(client.name);
    struct signal sig = new_disconnect_sig();
    write(client_socket, &sig, sizeof(sig));
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

int fetch_a_message(int socket_id, char *pipe_path, struct signal* sig) {
  int e;

  int pipe_id = open(pipe_path, O_RDONLY | O_NONBLOCK);
  if (pipe_id < 0) return -1;

  fd_set fd;
  FD_ZERO(&fd);
  FD_SET(socket_id, &fd);
  FD_SET(pipe_id, &fd);
  int m = socket_id > pipe_id ? socket_id : pipe_id;

  select(m+1, &fd, NULL, NULL, NULL);

  if ( FD_ISSET(socket_id, &fd) ) {
    e = read(socket_id, sig, sizeof(*sig));
  } else if ( FD_ISSET(pipe_id, &fd) ){
    e = read(pipe_id, sig, sizeof(*sig));
  } else {
    e = 0;
  };

  close(pipe_id);

  return e;
}

int handle_request(int socket_id, struct user client) {
  int e;
  struct signal sig;

  e = fetch_a_message(socket_id, client.name, &sig);
  if (e < 0) return -1;

  switch (sig.type) {
  case DISCONNECT:
    running = 0;
    break;
  case MESSAGE:
    if (is_to(sig.body.message, client)) {
      e = write(socket_id, &sig, sizeof(sig));
      if (e < 0) return -1;
    } else if (is_from(sig.body.message, client)) {
      int to_pipe = open(sig.body.message.to.name, O_WRONLY | O_NONBLOCK);
      if (to_pipe < 0) return 0;

      e = write(to_pipe, &sig, sizeof(sig));
      if (e < 0) return -1;
      close(to_pipe);

      printf("<%s> said %s to <%s>\n", sig.body.message.from.name, sig.body.message.text, sig.body.message.to.name);
    }
    break;
  }

  return e;
}

int handshake(int client_socket, struct user *client) {
  int e;
  struct signal sig;
  e = read(client_socket, &sig, sizeof(sig));
  if (e <= 0) return -1;

  *client = sig.body.handshake;

  e = mkfifo(client->name, 0600);
  if (e < 0) return -1;

  e = write(client_socket, &sig, sizeof(sig));
  if (e <= 0) return -1;

  return 0;
}
