#include <string.h>

#include "message.h"

struct user new_user(char *name) {
  struct user u;
  strncpy(u.name, name, MAX_USERNAME);
  return u;
}

int is_to(struct message message, struct user user) {
  return strcmp(message.to.name, user.name) == 0;
}

struct signal new_handshake_sig(struct user user) {
  union payload body = {
    .handshake = user
  };

  struct signal signal = {
    .type = HANDSHAKE,
    .body = body
  };

  return signal;
}

struct signal new_message_sig(struct user from, struct user to, char *text) {
  struct message message = {
    .from = from,
    .to = to
  };
  strncpy(message.text, text, MAX_MESSAGE);

  union payload body = {
    .message = message
  };

  struct signal signal = {
    .type = MESSAGE,
    .body = body
  };

  return signal;
}

struct signal new_disconnect_sig() {
  struct signal signal = {
    .type = DISCONNECT
  };

  return signal;
}
