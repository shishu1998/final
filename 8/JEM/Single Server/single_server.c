#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

  if (username == NULL && password == NULL)  {
    printf("Huzzah! You have entered a username and password that has no newline!\n");
    return 1;
  }
  else{
    printf("Please do not include newline character, white space, or underscore characters within your username and password. Please try again.\n");
    return 0;
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
    //printf("buffer after fread/fwrite: %s\n", buffer);
    fclose(fd);
    return 0;
  }
}

void sign_up(int socket_client) {
  char user[USER_LEN]; char pswd[PSWD_LEN];
  //char *username = (char *)malloc(USER_LEN*sizeof(char));
  //char *password = (char *)malloc(PSWD_LEN*sizeof(char));
  char *input = (char *)malloc(USER_LEN*sizeof(char));
  
  read(socket_client, user, msg_len);
  printf("username: %s\n", user);
  
  if (find_user_match(user) == 1) {
    write(socket_client, "Please provide a password: ", msg_len);
    read(socket_client, input, msg_len);
    printf("password: %s\n", input);
    
    char *username = calloc(strlen(user) + strlen(pswd) + strlen(&underscore) + 1, sizeof(char));
    strcat(username, user);
    //char *line = (char *)calloc(strlen(user) + strlen(pswd) + strlen(&underscore) + 1, sizeof(char));
    char *line = (char *)calloc(strlen(user)+strlen(pswd)+strlen(&underscore)+1,sizeof(char));
    line = strsep(&username, "\n");
    strcat(line, &underscore);
    strcat(line, pswd);
    printf("line: %s\n", line);
    
    FILE* fd1 = fopen("username.txt", "a+");
    fwrite(line, sizeof(char), strlen(line), fd1);
    //to do: redirect to log in page
    fclose(fd1);
  }

 else if (find_user_match(user) == 0) {
    write(socket_client, "The username you typed is already taken. Please run the program again", msg_len);
    //printf("Would you like to sign up again?Press y for yes and n for no.\n");
    exit(0);
 }
}

int find_user(int socket_client) {
  FILE* fd1 = fopen("username.txt", "r");
  char *username; char *password;
  char *line = (char*)malloc(sizeof(char)*250);
  //retrieves username and password
  read(socket_client, line, msg_len);
  //strtok(line, "\n");  
  printf("<server>line: %s\n", line);
  write(socket_client, "<from server>line received\n", msg_len);
  
  char *buffer = (char *)malloc(BUFFER_LEN*sizeof(char));
  fread(buffer, sizeof(char), BUFFER_LEN, fd1);
  printf("<server> buffer: %s\n", buffer);
  if (strstr(buffer, line) == NULL) {
    printf("find_user() returned NULL. You typed incorrectly.\n");
    return 0;
  }
  else {
    printf("HUZZAH. You are a valid user! \n");
    return 1;
  }
  return 0;
}


int main() {
  char* yes_or_no = (char*)malloc(sizeof(char)*10);
  char* input = (char*)malloc(sizeof(char)*250);
  char* buffer = (char*)malloc(sizeof(char)*250);
  int socket_id, socket_client, con_id;
  char *one_two = (char *)malloc(sizeof(char));

  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons(24601); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  listen( socket_id, 1 );
  
  for ( ; ; ) {
    
    socket_client = accept(socket_id, NULL, NULL); // blocking call 
    //int pid = fork();
    
    //if ( pid == 0 ) { //check for child
    
    close(socket_id);
    printf("<server> connected: %d\n", socket_client );
    //now you can do things
    //while( strcmp(input, "bye") != 0 ) {
    
    read(socket_client, buffer, msg_len);
    printf("one_two value:%s\n", buffer);
    write(socket_client, "Mary received your value...\n", msg_len);
    if (strcmp(buffer, "1") == 0) {//logging back in
      printf("input is 1 --> User is logging in\n ");
      if (find_user(socket_client) == 0) {
	//printf("try again!\n");
	exit(0);
      }
      else {//find_user(socket_client) == 1
	while( 1 ) {
	  printf("Talk to <client> : ");
	  //fgets(input, strlen(input), stdin);
	  fgets(input, msg_len, stdin);
	  //input = strsep(&input, "\n");
	  strtok(input, "\n");
	  //write( socket_client, input, strlen(input));
	  write( socket_client, input, msg_len );
	  if ( strcmp( input, exit_sig ) == 0 ) {
	    printf(">> Are you sure you want to exit?\n");
	    printf(">> type 'y' for yes\n>> type 'n' for no\n");
	    fgets( yes_or_no, 10, stdin);
	    strtok(yes_or_no, "\n");
	
	    if ( strlen(yes_or_no) > 1 ) {
	      printf( ">> Looks like you goofed!  Better just keep chatting...\n");
	      printf( "Wait for your partner to respond...\n");
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
	  //read( socket_client, buffer, strlen(buffer));
	  read( socket_client, buffer, msg_len);
	  printf("<server> received: [%s]\n", buffer );
	}//while loop
      }
      close(socket_client);
      exit(0); 
    }
    else if (strcmp(buffer, "2") == 0){
      printf("input is 2 --> User is creating an account\n ");
      sign_up(socket_client);
    }   
  }//end bracket for forever loop
  return 0;
}

