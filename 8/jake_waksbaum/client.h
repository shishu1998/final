#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>

#define IP "127.0.0.1"

int connect_to_server(char * ip, int port);
int is_exit(char *);
int send_request(char *req, size_t len, int socket_id);
int handle_response(int socket_id);

#endif
