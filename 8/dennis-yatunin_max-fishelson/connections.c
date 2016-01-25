#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define PORT_STR "8000"
#define PORT_INT 8000

typedef struct ip_or_name {
	int is_ip;
	char *ip;
	char *hostname;
} ip_or_name;

void error(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int open_client_socket(ip_or_name *ion) {
	int sock;

	if (ion->is_ip) {
		struct sockaddr_in server;

		sock = socket(AF_INET , SOCK_STREAM , 0);
		if (sock == -1) {
			error("socket");
		}

		server.sin_addr.s_addr = inet_addr(ion->ip);
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT_INT);

		if (connect(sock, (struct sockaddr *)&server , sizeof(server)) == -1) {
			if (errno == ECONNREFUSED) {
				errno = 0;
				return 0;
			}
			error("connect");
		}
	}

	else {
		struct addrinfo hints, *res;
		int err;

		memset(&hints, 0, sizeof(hints));
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_family = AF_INET;

		if ((err = getaddrinfo(ion->hostname, PORT_STR, &hints, &res)) != 0) {
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
	}

	return sock;
}