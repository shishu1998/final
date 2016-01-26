#ifndef SERVER_H
#define SERVER_H

#include "message.h"

int setup_server(int port);
int handle_request(int socket, struct user client);
int handshake(int client_socket, struct user* client);
int send_message(int socket_id, char *);

#endif
