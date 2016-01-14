#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_LINE 256
#define MAX_NAME_LENGTH 32

/* 
 * 0: Merlin
 * 1: Percival
 * 2: Guy
 * 3: Morgana
 * 4: Assassin
 */

void storename(char name[]) {
  printf("Enter your name.\n");
  fgets(name, MAX_NAME_LENGTH, stdin);
  name = strtok(name, "\n");
  printf("Welcome, %s.\n", name);
}

void parse_input() {
  printf("inputinput\n");
  char input[MAX_LINE];
  fgets(input, MAX_LINE, stdin);
  if(input[0] == '/') {
    printf("input: %s", input);
  }
}

/* 
 * Should prompt to pick team members
 * Check if the prompted team members exist within the list, then make sure 
 *  the user picks the appropriate number of team members
 */
void pick_members(char* list, int number) {
  return;
}

/*
 * Derrick TODO:
 * Set up client prompt (should print [Chat])
 */

int main() {
  char name[MAX_NAME_LENGTH];

  storename(name);

  while(1) {
    parse_input();
  }

  return 0;

  int socket_id;
  char buffer[256];
  int i;

  //create the socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);
  
  //bind to port address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(5000);
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));

  //attempt connection
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);
  
  read(socket_id, buffer, sizeof(buffer));
  printf("<client> received [%s]\n", buffer);

  return 0;
}
