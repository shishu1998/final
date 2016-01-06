#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void process( char *s ) {
	while ( *s ) {
		*s = (*s - 'a' + 13) % 26 + 'a';
		s++;
	}
}

static void sighandler(int signo) {
	// get rid of the annoying mario
	// can't figure out how to get rid of the other pipes
	if (signo == SIGINT) {
		remove("mario");
		exit(0);
	}
}

int server_handshake( int *from_client ) {
	int to_client;
	char buffer[100];

	mkfifo( "mario", 0644 ); //create WKP
	*from_client = open( "mario", O_RDONLY ); //Open & wait for connect
	remove( "mario" ); //once connected, remove the pipe file


	int f = fork();
	if (f == 0) {
		read( *from_client, buffer, sizeof(buffer) ); //read from client
		printf( "<server> connection established: [%s]\n", buffer );
		to_client = open(buffer, O_WRONLY);

		strncpy( buffer, "its-a-me, mario!", sizeof(buffer) );
		write( to_client, buffer, sizeof(buffer) ); //send initial message

		return to_client;
	} else {
		return 0;
	}
}


void client_connection( int to_client, int from_client ) {
	char buffer[100];
	printf("before client_connection while loop\n");
	while( read( from_client, buffer, sizeof(buffer) ) ) {
		printf( "<server> received [%s]\n", buffer );
		printf("right before process\n"); //debugging
		process( buffer );
		printf("buffer after process: %s\n", buffer); //debugging
		write( to_client, buffer, sizeof(buffer) );
		strncpy( buffer, "", sizeof(buffer) );
	}
}

int main() {
	signal(SIGINT, sighandler);

	int to_client;
	int from_client;
	//char buffer[100];

	while (1) {
		printf("<server> waiting for connection\n");
		to_client = server_handshake(&from_client);

		if (to_client != 0) {
			client_connection(to_client, from_client);
			close(to_client);
		}
	}

	return 0;
}
