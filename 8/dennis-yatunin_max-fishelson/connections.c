#include "utils.h"
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int client_open_sock_addr(char *addr) {
	struct sockaddr_in server;
	int sock;

	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1) {
		error("socket");
	}

	server.sin_addr.s_addr = inet_addr(addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT_INT);

	if (connect(sock, (struct sockaddr *)&server , sizeof(server)) == -1) {
		if (errno == ECONNREFUSED) {
			errno = 0;
			return 0;
		}
		error("connect");
	}

	return sock;
}

int client_open_sock_name(char *name) {
	struct addrinfo hints, *res;
	int err, sock;

	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;

	if ((err = getaddrinfo(name, PORT_STR, &hints, &res)) != 0) {
		printf("getaddrinfo: %s\n", gai_strerror(err));
		return 0;
	}

	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock == -1) {
		error("socket");
	}

	if (connect(sock, res->ai_addr, res->ai_addrlen) == -1) {
		if (errno == ECONNREFUSED) {
			errno = 0;
			return 0;
		}
		error("connect");
	}

	return sock;
}

void send_and_recieve(int sock, char *data, int data_size, char *buf, int buf_size) {
	if(write(sock, data, data_size) < 0) {
		error("send");
	}

	if(read(sock, buf, buf_size) < 0) {
		error("recv");
	}
}

int server_open_sock() {
	struct sockaddr_in server;
	int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		error("socket");
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT_INT);

	if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1) {
		error("bind");
	}

	if (listen(sock , 16)) {
		error("listen");
	}

	return sock;
}

int server_connect_sock(int sock) {
	struct sockaddr_in client;
	int c = sizeof(struct sockaddr_in);
	int client_sock;

	client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c);
	if (client_sock == -1) {
		error("accept");
	}

	return client_sock;
}