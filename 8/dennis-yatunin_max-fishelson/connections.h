#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#define PORT_STR "8000"
#define PORT_INT 8000

int client_to_server_addr(char *addr);

int client_to_server_name(char *name);

int server_listener();

int server_to_client(int listening_sock);

#endif
