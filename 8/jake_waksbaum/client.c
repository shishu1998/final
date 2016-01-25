#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "len_prefix.h"
#include "hostname.h"
#include "shared.h"
#include "client.h"

static int running = 1;

int main(int argc, char * argv[]) {
  int socket_id, e;
  char * hostname;

  hostname = check_args(argc, argv);

  setup_sig_handler();

  socket_id = connect_to_server(hostname, PORT);

  while (running) {
    e = run(socket_id);
    if (e <= 0) running = 0;
  }

  close(socket_id);
}

char * check_args(int argc, char * argv[]) {
  if (argc < 2) {
    printf("Usage: client <hostname>\n");
    exit(1);
  } else {
    return argv[1];
  }
}

int run(int socket_id) {
  int bytes_read, e;
  char input[256];

  e = get_input(input, sizeof(input), &bytes_read);
  if (e < 0 && errno == EINTR) return e;

  if (!running) {
    return 0; // we usually C-c or exit during input
  }

  e = send_request(input, bytes_read, socket_id);
  if (e < 0) return e;

  e = handle_response(socket_id);

  return e;
}

int get_input(char * input, int input_size, int *bytes_read) {
  int e;
  printf("> ");
  fflush(stdout);

  e = *bytes_read = read(STDIN_FILENO, input, input_size-1);
  input[*bytes_read++] = '\0';

  if (*bytes_read == 1) {
    running = 0;
  }

  return e;
}

int connect_to_server(char * hostname, int port) {
  int socket_id, e;

  // create socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  struct in_addr *addr;
  e = hostname_to_ip(hostname, &addr);
  printf("%s\n", inet_ntoa(*addr));

  // bind to port/address
  struct sockaddr_in sock = {
    .sin_family = AF_INET,
    .sin_port = htons(port),
    .sin_addr = *addr
  };

  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));

  // attempt a connection
  e = connect(socket_id, (struct sockaddr*)&sock, sizeof(sock));
  if (e < 0) return e;

  return socket_id;
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


static void sighandler(int signo) {
  if (signo == SIGINT) {
    running = 0;
  }
}

void setup_sig_handler() {
  struct sigaction action = {
    .sa_handler = sighandler,
    .sa_flags = 0
  };
  sigemptyset(&action.sa_mask);

  sigaction(SIGINT, &action, NULL);
}
