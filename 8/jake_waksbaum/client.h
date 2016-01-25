#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>

char * check_args(int, char * []);
void setup_sig_handler();
int run(int socket_id);
int get_input(char * input, int input_size, int *bytes_read);
int connect_to_server(char * ip, int port);
int send_request(char *req, size_t len, int socket_id);
int handle_response(int socket_id);

#endif
