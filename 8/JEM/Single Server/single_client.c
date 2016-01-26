#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
//#include "login.h"
#define USER_LEN 20
#define PSWD_LEN 20
#define BUFFER_LEN 500
const char underscore = '_';

int find_error(char *username, char *password) {
  //printf("Running find_error()...\n");
  if (username == NULL || password == NULL) {
    printf("username and password cannot be null.\n");
    return 0;
  }
  strsep(&username, " _");
  strsep(&password, " _");
  //printf("username: %s\n", username);
  //printf("password: %s\n", password);
  if (username == NULL && password == NULL)  {
    printf("Huzzah! You have entered a username and password that has no newline!\n");
    return 1;
  }
  else{
    printf("Please do not include newline character, white space, or underscore characters within your username and password. Please try again.\n");
    return 0;
  }
}

void sign_up(char input) {
  char user[USER_LEN]; char pswd[PSWD_LEN];
  char *username;
  while(input == 'y') {//y is yes, n is no
    FILE* fd1 = fopen("username.txt", "a+");
    printf("Please create a username:\n");
    fgets(user, USER_LEN, stdin);
    printf("Please create a password:\n");
    fgets(pswd, PSWD_LEN, stdin);
    //printf("username array: %s\n", user);
    //printf("pswd array: %s\n", pswd);
    username = calloc(strlen(user) + strlen(pswd) + strlen(&underscore) + 1, sizeof(char));
    strcat(username, user);
    char *line = (char *)calloc(strlen(user) + strlen(pswd) + strlen(&underscore) + 1, sizeof(char));
    line = strsep(&username, "\n");
    strcat(line, &underscore);
    //printf("username: %s\n", username);
    strcat(line, pswd);
    printf("line: %s\n", line);
    if (find_user_match(user) == 1) {
      fwrite(line, sizeof(char), strlen(line), fd1);
      //to do: redirect to log in page
    }
    else if (find_user_match(user) == 0) {
      fclose(fd1);
      printf("Would you like to sign up again?Press y for yes and n for no.\n");
      char response;
      response = getchar();//response, 2, stdin);
      if (response == 'n') {
	input = 'n';
	exit(0); //add ability to log in directly??
      }
    }
  }
}

int find_user_match(char *username) {
  FILE* fd = fopen("username.txt", "r");
  char *buffer = (char *)malloc(BUFFER_LEN*sizeof(char));
  fread(buffer, sizeof(char), BUFFER_LEN, fd);
  username = strsep(&username, "\n");
  printf("username:%s\n", username);
  printf("buffer: %s\n", buffer);
  if (strstr(buffer, username) == NULL) {//if username isn't taken                                                                                                                   
    printf("find_user_match() returned NULL. Your username is acceptable.\n");
    buffer = "";
    fclose(fd);
    return 1;
  }
  else {
    printf("Your username is taken. Please try again.\n");
    buffer = "";
    printf("buffer after fread/fwrite: %s\n", buffer);
    fclose(fd);
    return 0;
  }
}
/*
Returns 1 if user input is correct. Returns 0 if not.
Log-in for returning users
 */
int find_user() {
  FILE* fd1 = fopen("username.txt", "r");//open username.txt                                                                                                                         
  char user[USER_LEN]; char pswd[PSWD_LEN];
  char *username;
  //retrieves username and password                                                                       
  printf("Please type in your username:\n");
  fgets(user, USER_LEN, stdin);
  printf("Please type in your password:\n");
  fgets(pswd, PSWD_LEN, stdin);

  if (find_error(user, pswd) == 1) {
    username = calloc(strlen(user) + strlen(pswd) + 1 + 1, sizeof(char));//1 is for the underscore and the other is for the null char                                                
    strcat(username, user);
    char *line = (char *)calloc(strlen(user) + strlen(pswd) + 1 + 1, sizeof(char));
    line = strsep(&username, "\n");
    strcat(line, &underscore);
    strcat(line, pswd);
    printf("line: %s\n", line);

    char *buffer = (char *)malloc(BUFFER_LEN*sizeof(char));
    fread(buffer, sizeof(char), BUFFER_LEN, fd1);
    //printf("strlen(buffer) = %lu\n", strlen(buffer));                                                                                                                              
    printf("buffer: %s\n", buffer);
    if (strstr(buffer, line) == NULL) {
      printf("find_user() returned NULL. You typed incorrectly.\n");
      return 0;
    }
    else if (find_error(user, pswd) == 0) {
      printf("find_error returned 0\n");
      return 0;
    }
    else {
      printf("HUZZAH. You are a valid user! \n");
      return 1;
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  int socket_id;
  //char input[256];
  //char buffer[256];
  char* yes_or_no = (char*)malloc(sizeof(char)*10);

  char* input = (char*)malloc(sizeof(char)*250);
  char* buffer = (char*)malloc(sizeof(char)*250);
  int i;
  char one_two;
  
  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;   
  sock.sin_port = htons(24601);
  //Set the IP address to connect to
  //127.0.0.1 is the "loopback" address of any machine
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));
  
  printf("=======WELCOME TO MARY'S PROM DATE SERVER=======\nYou want to take Mary out to PROM because she is an awesome person and if you don't want to then you have bad taste in \
women.\n\n");
  printf("Please type in 1 if you have an account or 2 if you'd like to make one.\n");
  fgets(&one_two, 3, stdin);
  printf("one_two value:%c\n", one_two);
  
  if (one_two == '1') {
    if (find_user() == 0) {//invalid
      printf("try again!\n");
      exit(0);
      }
    else { //if (find_user() == 1) {//valid
      printf("find_user() returned 1. Your user input is valid.\n");
      //attempt a connection
      i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
      printf("<client> connect returned: %d\n", i);
      if ( i < 0 ){
	printf("We're sorry, you failed to connect to the server.  Please try again.\n");
	exit(0);
      }
      //while (strcmp(buffer, "bye") != 0) {
      while( 1 ) {
	//read( socket_id, buffer, strlen(buffer));
	read( socket_id, buffer, msg_len);
	printf("<client> received: [%s]\n", buffer );
	printf("Talk to <server> : ");
	//fgets(input, strlen(input), stdin);
	fgets(input, msg_len, stdin);
	strtok(input, "\n");
	//write( socket_id, input, strlen(input));
	write( socket_id, input, msg_len);
	if ( strcmp( input, exit_sig ) == 0 ) {
	  printf(">> Are you sure you want to exit?\n");
	  printf(">> type 'y' for yes\n>> type 'n' for no\n");
	  fgets( yes_or_no, 10, stdin);
	  strtok(yes_or_no, "\n");
	  
	  if ( strlen(yes_or_no) > 1 ) {
	    printf( ">> Looks like you goofed!  Better just keep chatting...\n");
	  }
	  else if ( strcmp( yes_or_no, "y" ) == 0) {
	    printf(">> You're gone!\n");
	    exit(0);
	  }
	  else {
	    printf( ">> Then why did you say bye???\n" );
	    printf( "Wait for your partner to respond...\n");
	  }
	}
      }
    }
  }
  if (one_two == '2') {
    sign_up('y');
  }
  return 0;
}
