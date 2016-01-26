#ifndef SERVER_H
#define SERVER_H

#include "message.h"

int setup_server(int port);
int handle_request(int socket, int pipe_id, struct user client);
int handshake(int client_socket, struct user* client, int *pipe_id);
int send_message(int socket_id, char *);

#endif
