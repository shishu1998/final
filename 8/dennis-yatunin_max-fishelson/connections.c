#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#typedef struct name_or_ip {

};

void error(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

// Usage: client("localhost", "8000")
// service = port number or service name
int client(char *hostname, char *service) {
	struct addrinfo hints, *res;
	int err, sock;

	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;

	if ((err = getaddrinfo(hostname, service, &hints, &res)) != 0) {
		printf("getaddrinfo: %s\n", gai_strerror(err));
		return 1;
	}

	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock < 0) {
		error("socket");
	}

	if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
		error("connect");
	}

	freeaddrinfo(res);

	return 0;
}