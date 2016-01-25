#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8532

#define MAX_CLIENTS 10

#define MATH_ID 2
#define SCIENCE_ID 3
#define HISTORY_ID 4

#define TUTOR_ID 0
#define TUTEE_ID 1

int create_server() {
    int socket_id;
	
    //create the socket
    socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
    //bind to port/address
    struct sockaddr_in listener;
    listener.sin_family = AF_INET;  //socket type IPv4
    listener.sin_port = htons(PORT); //port #
    listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
    bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
    listen( socket_id, 1 );
	
    return socket_id;
}

void relay_msg(int client_from, int client_to) {
	char msg[100];
	sleep(1);
	read(client_from, msg, sizeof(msg));
	printf("<server> received [%s]\n", msg);
	write(client_to, msg, sizeof(msg));
	printf("<server> sent [%s]\n", msg);
}

int find_tutor(int tutors[MAX_CLIENTS][5], int num_tutors, int tutees[MAX_CLIENTS][3], int tutee_ind) {
	int subj = tutees[tutee_ind][2];
	int tutor_ind = -1;
	int max_skill = 0;
	int i;
	for (i = 0; i < num_tutors; i++) {
		if (tutors[i][1] == 0) {
			if (tutors[i][subj] > max_skill) {
				tutor_ind = i;
				max_skill = tutors[i][subj];
			}
		}
	}
	return tutor_ind;
}

static void sighandler(int signo) {
	if (signo == SIGINT) {
		printf("Server closing\n");
		exit(0);
	}
}

int main() {
  signal(SIGINT, sighandler);

  int socket_id, socket_client;
  
  /* stores tutor client info
  * 	0: client socket id
  *		1: availability - 0 (free), 1 (in chat)
  *		2: math skill
  *		3: science skill
  *		4: history skill
  **/
  int tutors[MAX_CLIENTS][5] = { 0 }; 
  int num_tutors = 0;
  
  /* stores tutee client info
  *		0: client socket id
  * 	1: availability - 0 (free), 1 (in chat)
  * 	2: subject - 2 (math), 3 (science), 4 (history)
  **/
  int tutees[MAX_CLIENTS][3] = { 0 };
  int num_tutees = 0;
  
  socket_id = create_server();

  while(1) {
	 
  	printf("<server> listening: %d\n", socket_id);
  	socket_client = accept( socket_id, NULL, NULL );
  	printf("<server> connected: %d\n", socket_client );
	
	int type = TUTOR_ID;  // get type from client
	if (type == TUTOR_ID) {
		if (num_tutors < MAX_CLIENTS) {
			printf("Adding tutor - %d\n", socket_client);
			tutors[num_tutors][0] = socket_client;
			tutors[num_tutors][1] = 1;
			num_tutors++;
			printf("# tutors %d\n", num_tutors);
		}
		else {
			char msg[100];
			sprintf(msg, "XSorry, too many clients. Come back later.\n");
			write(socket_client, msg, sizeof(msg));
			close(socket_client);
		}
	}
	else {
		if (num_tutees < MAX_CLIENTS) {
			printf("Adding tutee\n");
			tutees[num_tutees][0] = socket_client;
			tutees[num_tutees][1] = 1;
			num_tutees++;
		}
		else {
			char msg[100];
			sprintf(msg, "XSorry, too many clients. Come back later.\n");
			write(socket_client, msg, sizeof(msg));
			close(socket_client);
		}
	}
	
	printf("%d\n", tutors[0][0]);
	printf("%d\n", tutors[1][0]);

	int pid = fork();
    if (pid == 0){
		if (num_tutors >= 2) {  // find_tutor(tutors, num_tutors, tutees, num_tutees-1) 
			char msg[] = "You have been connected to a tutor.";
			write(tutors[0][0], msg, sizeof(msg));

			while(1) {
				relay_msg(tutors[0][0], tutors[1][0]);
			//	sleep(2);
				relay_msg(tutors[1][0], tutors[0][0]);
			}
		}

		/*
		while(1) {  
      		//system("gnome-terminal"); -> this is how to open a new window but u cant control it
      		printf("Enter text to write:\n");
     		char s[100];
      		fgets(s, sizeof(s), stdin);
      		write(socket_client, s, sizeof(s));
      		printf("<server> waiting\n");
      		sleep(2);
      		read(socket_client, s, sizeof(s));
      		printf("<server> received: %s\n", s);
		}
		**/

    } else {
      close(socket_client);
    }
  }

  return 0;
}
