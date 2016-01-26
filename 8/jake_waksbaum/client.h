#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include "message.h"

void setup_sig_handler();
int send_messages(int socket_id, struct user);
int read_message(struct message *, struct user me);
int send_message(int socket_id, struct message*);
int get_input(char * input, int input_size);
int connect_to_server(char * ip, int port);
int handshake(int socket_id, struct user);
int send_request(char *req, size_t len, int socket_id);
int receive_messages(int socket_id);
void cleanup(int socket_id);

#endif
