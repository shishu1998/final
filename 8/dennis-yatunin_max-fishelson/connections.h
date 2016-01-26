#ifndef CONNECTIONS_H
#define CONNECTIONS_H

int client_open_sock_addr(char *addr)

int client_open_sock_name(char *name)

void send_and_recieve(int sock, char *data, int data_size, char *buf, int buf_size)

int server_open_sock()

int server_connect_sock(int sock)

#endif
