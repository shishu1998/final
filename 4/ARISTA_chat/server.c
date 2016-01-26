#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "connection.h"

#define MAX_CLIENTS 10

#define MATH_ID 2
#define SCIENCE_ID 3
#define HISTORY_ID 4

/* stores tutor client info
  * 0: client socket id
  *	1: availability - 0 (free), 1 (in chat)
  *	2: math skill
  *	3: science skill
  *	4: history skill
  **/
int tutors[MAX_CLIENTS][5] = { 0 }; 
int num_tutors = 0;
  
/* stores tutee client info
  *	0: client socket id
  * 1: availability - 0 (free), 1 (in chat)
  * 2: subject - 2 (math), 3 (science), 4 (history)
  **/
int tutees[MAX_CLIENTS][3] = { 0 };
int num_tutees = 0;


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

int relay_msg(int client_from, int client_to) {
	char msg[100];
	sleep(1);
	read(client_from, msg, sizeof(msg));
	printf("<server> received [%d->]: %s", client_from, msg);
	if (strcmp(msg, "exit\n") == 0) {
		return -1;
	}
	write(client_to, msg, sizeof(msg));
	printf("<server> sent [->%d]: %s", client_to, msg);
	return 1;
}

int find_tutor(int tutee_ind) {
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

/* find tutor without subject consideration */
int find_tutor_simp(int tutee_ind) {
	int i;
	for (i = 0; i < num_tutors; i++) {
		if (tutors[i][1] == 0)
			return i;
	}
	return -1;
}

void close_chat(int tutor_ind, int tutee_ind) {
	int i;
	
	// set tutor to available
	tutors[tutor_ind][1] = 0;

	// close tutee connection
	close(tutees[tutee_ind][0]);
	num_tutees--;
	for (i = tutee_ind; i < num_tutees; i++) {
		int j;
		for (j = 0; j < 3; j++) {
			tutees[tutee_ind][j] = tutees[tutee_ind+1][j];	
		}
	}
}

void close_tutor(int tutor_ind) {
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
  
  socket_id = create_server();

  while(1) {
	 
  	printf("<server> listening: %d\n", socket_id);
  	socket_client = accept( socket_id, NULL, NULL );
	sleep(2);
  	printf("<server> connected: %d\n", socket_client );
	
	/* add client to corresponding array */
	int type;  // get type from client
	read(socket_client, &type, sizeof(type));
	if (type == TUTOR_ID) {
		if (num_tutors < MAX_CLIENTS) {
			tutors[num_tutors][0] = socket_client;
		//	tutors[num_tutors][1] = 1;
			num_tutors++;
			printf("<server> added tutor: %d [%d tutors; %d tutees]\n", socket_client, num_tutors, num_tutees);
		}
		else {
			char msg[100];
			sprintf(msg, "XSorry, too many clients. Come back later.\n");
			write(socket_client, msg, sizeof(msg));
			close(socket_client);
		}
	}
	else if (type == TUTEE_ID) {
		if (num_tutees < MAX_CLIENTS) {
			tutees[num_tutees][0] = socket_client;
			tutees[num_tutees][1] = 1;
			// insert tutee subject requested
			num_tutees++;
			printf("<server> added tutee: %d [%d tutors; %d tutees]\n", socket_client, num_tutors, num_tutees);
		}
		else {
			char msg[100];
			sprintf(msg, "XSorry, too many clients. Come back later.\n");
			write(socket_client, msg, sizeof(msg));
			close(socket_client);
		}
	}
	else {
		printf("ERROR - type argument\n");
	}

	/* start chat from tutee side */
	if (type == TUTEE_ID) {	
		int tutee_ind = num_tutees-1;
		int tutor_ind = find_tutor_simp(tutee_ind);
		if (tutor_ind != -1) {
			int status;
			printf("<server> paired tutor #%d and tutee #%d\n", tutor_ind, tutee_ind);
			tutors[tutor_ind][1] = 1;  // set tutor to unavailable
			int pid = fork();  // subserver 
    		if (pid == 0) {
				char msg[] = "You have been connected to a tutor.";
				write(tutees[tutee_ind][0], msg, sizeof(msg));
				int run = 1;	
				while(run) {
					int e = relay_msg(tutees[tutee_ind][0], tutors[tutor_ind][0]);
					if (e == -1) {
						run = 0;
					}
					relay_msg(tutors[tutor_ind][0], tutees[tutee_ind][0]);
				}
			}
			/**
		   	else {
				waitpid(pid, &status, 0);  // wait for chat to finish
				printf("<server> closing chat between tutor #%d and tutee #%d\n", tutor_ind, tutee_ind);
				close_chat(tutor_ind, tutee_ind);
			}
			*/
		}
	} else {
		// shift array down, adjust
        // close(socket_client);
    }
  }

  return 0;
}
