#ifndef MESSAGE_H
#define MESSAGE_H

#define MAX_MESSAGE 512
#define MAX_USERNAME 64

#define HANDSHAKE 1
#define MESSAGE 2
#define DISCONNECT 3

struct user {
  char name[MAX_USERNAME];
};

struct message {
  struct user from;
  struct user to;
  char text[MAX_MESSAGE];
};

union payload {
  struct message message;
  struct user handshake;
};

struct signal {
  int type;
  union payload body;
};


struct user   new_user(char *name);
struct signal new_handshake_sig(struct user user);
struct signal new_message_sig(struct user from, struct user to, char *text);
struct signal new_disconnect_sig();

#endif
