#include "utils.h"
#include "connections.h"
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int client_to_server_addr(char *addr) {
	struct sockaddr_in server;
	int sock_to_server;

	sock_to_server = socket(AF_INET , SOCK_STREAM , 0);
	if (sock_to_server == -1) {
		error("socket");
	}

	server.sin_addr.s_addr = inet_addr(addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT_INT);

	if (
		connect(
			sock_to_server, (struct sockaddr *)&server , sizeof(server)
			) == -1
		) {
		if (errno == ECONNREFUSED) {
			errno = 0;
			return -1;
		}
		error("connect");
	}

	return sock_to_server;
}

int client_to_server_name(char *name) {
	struct addrinfo hints, *res;
	int err, sock_to_server;

	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;

	if ((err = getaddrinfo(name, PORT_STR, &hints, &res)) != 0) {
		printf("getaddrinfo: %s\n", gai_strerror(err));
		exit(EXIT_FAILURE);
	}

	sock_to_server = socket(
		res->ai_family, res->ai_socktype, res->ai_protocol
		);
	if (sock_to_server == -1) {
		error("socket");
	}

	if (connect(sock_to_server, res->ai_addr, res->ai_addrlen) == -1) {
		if (errno == ECONNREFUSED) {
			errno = 0;
			return -1;
		}
		error("connect");
	}

	return sock_to_server;
}

int server_listener() {
	struct sockaddr_in server;
	int listening_sock;

	listening_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listening_sock == -1) {
		error("socket");
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT_INT);

	if (
		bind(
			listening_sock, (struct sockaddr *)&server, sizeof(server)
			) == -1
		) {
		error("bind");
	}

	if (listen(listening_sock , 16) == -1) {
		error("listen");
	}

	return listening_sock;
}

int server_to_client(int listening_sock) {
	struct sockaddr_in client;
	int c = sizeof(struct sockaddr_in);
	int sock_to_client;

	sock_to_client = accept(
		listening_sock, (struct sockaddr *)&client, (socklen_t *)&c
		);
	if (sock_to_client == -1) {
		error("accept");
	}

	return sock_to_client;
}
