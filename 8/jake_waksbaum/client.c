#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "hostname.h"
#include "message.h"
#include "shared.h"
#include "client.h"

static int running = 1;

int main(int argc, char * argv[]) {
  int socket_id, e;
  char *hostname, *username;
  int sending = 0;

  if (argc < 3) {
    printf("Usage: client <hostname> <username>\n");
    exit(1);
  } else {
    hostname = argv[1];
    username = argv[2];
    if (argc >= 4) {
      sending = 1;
    };
  }

  struct user me = new_user(username);

  setup_sig_handler();

  e = socket_id = connect_to_server(hostname, PORT);
  if (e < 0) check_errors("Error connecting to server", e);

  e = handshake(socket_id, me);
  if (e < 0) {
    printf("Username already taken\n");
    running = 0;
  } else {
    printf("Handshake succesfull!\n");
  }

  while (running) {
    if (sending) {
      e = send_messages(socket_id, me);
    } else {
      e = receive_messages(socket_id);
    }
    if (e < 0) running = 0;
  }

  cleanup(socket_id);
}

int send_messages(int socket_id, struct user me) {
  int e;

  struct message message;
  e = read_message(&message, me);
  if (e < 0 && errno == EINTR) return e;

  if (!running) {
    return 0; // we usually C-c or exit during input
  }

  printf("About to send %s your message...", message.to.name);
  fflush(stdout);

  e = send_message(socket_id, &message);
  if (e < 0) return e;

  printf(" sent!\n");

  return 0;
}

int read_message(struct message *message, struct user me) {
  int bytes_read;
  struct user to;

  message->from = me;

  printf("Message Recipient: ");
  fflush(stdout);
  bytes_read = get_input(to.name, MAX_USERNAME);
  if (bytes_read <= 0) return -1;

  message->to = to;

  printf("Message: \n");
  bytes_read = get_input(message->text, MAX_MESSAGE);
  if (bytes_read <= 0) return -1;

  return 0;
}

int send_message(int socket_id, struct message *message) {
  struct signal sig = new_message_sig(message->from, message->to, message->text);
  return write(socket_id, &sig, sizeof(sig));
}

int get_input(char * input, int input_size) {
  int bytes_read;

  bytes_read = read(STDIN_FILENO, input, input_size-1);
  input[bytes_read-1] = '\0'; // replace newline

  if (bytes_read <= 0) {
    printf("Exiting...\n");
    running = 0;
  }

  return bytes_read;
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

int handshake(int socket_id, struct user user) {
  int e;
  struct signal sig = new_handshake_sig(user);
  e = write(socket_id, &sig, sizeof(sig));
  if (e <= 0) return -1;

  read(socket_id, &sig, sizeof(sig));
  if (e <= 0) return -1;

  if (sig.type != HANDSHAKE && strcmp(user.name, sig.body.handshake.name) != 0) {
    return -1;
  }

  return 0;
}

int receive_messages(int socket_id) {
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
    break;
  }

  return 0;
}

void cleanup(int socket_id) {
  struct signal sig = new_disconnect_sig();
  write(socket_id, &sig, sizeof(sig));
  close(socket_id);
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
