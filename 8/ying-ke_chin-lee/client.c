#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int client_handshake( int *from_server ) {

	int to_server;
	char buffer[100];

	sprintf( buffer, "%d", getpid() );
	mkfifo( buffer, 0644 );

	//to_server = open( "mario", O_WRONLY|O_NONBLOCK );
	to_server = open( "mario", O_WRONLY);
	write( to_server, buffer, sizeof(buffer) );

	printf("toserver = %d\n", to_server);
	printf("got here?  buffer = %s\n", buffer); // line below has issue
	*from_server = open( buffer, O_RDONLY);

	remove( buffer );

	read( *from_server, buffer, sizeof(buffer) );
	printf("<client> connection established: [%s]\n", buffer );

	return to_server;
}


int main() {
	int logged_in = 0;
	int valid_login = 1; // for the sake of simplicity atm

	int to_server;
	int from_server;
	char buffer[100];

	char uname[30];
	char pwd[30];

	to_server = client_handshake( &from_server );

	while (1) {
		if (!logged_in) {
			printf("<client> Welcome!\nUsername: ");
			fgets( uname, sizeof(uname), stdin );
			*strchr( uname, '\n') = 0;

			printf("<client> Password: ");
			fgets( pwd, sizeof(pwd), stdin );
			*strchr( pwd, '\n') = 0;

			if (!valid_login) {
				printf("<client> Invalid login.  Program quitting.\n");
				exit(0);
			} 
			printf("<client> Login successful.\n");
			logged_in = 1;
		}

		printf("<client> enter stuff: ");
		fgets( buffer, sizeof(buffer), stdin );
		*strchr( buffer, '\n') = 0;

		if (strcmp(buffer, "exit") == 0) {
			return 0;
		}

		write( to_server, buffer, sizeof(buffer) );
		read( from_server, buffer, sizeof(buffer) );
		printf("<client> received: [%s]\n", buffer );
	}

	close( to_server );
	close( from_server );

	return 0;
}
