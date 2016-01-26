#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define PORT_STR "8000"
#define PORT_INT 8000

void error(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int open_client_socket_addr(char *addr) {
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

int open_client_socket_name(char *name) {
	struct addrinfo hints, *res;
	int err, sock;

	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;

	if ((err = getaddrinfo(name, PORT_STR, &hints, &res)) != 0) {
		printf("getaddrinfo: %s\n", gai_strerror(err));
		return 1;
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

int main() {
	printf("socketfd: %d", open_client_socket_name("www.google.com"));
}