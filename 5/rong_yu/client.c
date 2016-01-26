#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

char name[50];

int client_handshake(int *from_server){
  int to_server;
  char buffer[100];
  
  //sprintf( buffer, "%d", getpid() ); //sprintf prints the getpid() to buffer
  printf("Username: ");
  fgets(buffer, 99, stdin);

  *strchr(buffer, '\n') = 0;

  //printf("Name: %s\n", buffer);
  
  strcat(name, buffer);
  printf("Name: %s\n", buffer);
  mkfifo( buffer, 0644);
  to_server = open( "mario", O_WRONLY );
  write( to_server, buffer, sizeof(buffer) );
  
  printf("<Client> has sent Named Pipe Name to the <Server>\n");
  printf("<Client> is waiting for <Server> to respond\n");
  *from_server = open(buffer, O_RDONLY);
  //printf("<Server> has responded. \n");
  remove(buffer);
  read(*from_server, buffer, sizeof(buffer) );

  printf("<Server> has responded, <Client> has now removed the Named Pipe\n");
  
  printf("<client> connection established: [%s]\n", buffer );
  return to_server;
  
}

int main(){
  int to_server;
  int from_server;
  char buffer[100];
  char to_who[50];
  //char name[50];
  char message[500];
  //char SPLIT[18] = "010203040506070809";
  char SPLIT[3] = "\n";
  

  to_server = client_handshake( &from_server);
  
  while (1){
    
    int i = 0;
    while (buffer[i]){
      buffer[i] = 0;
      i++;
    }
    
    printf("<client> Who do you want to bother? \n");
    fgets( to_who, sizeof(to_who), stdin);
    *strchr(to_who, '\n') = 0; //strchr returns a pointer of the first occurance
    if ( strcmp( to_who, "exit") == 0){
      exit(1);
    }
    printf("<client> What do you want to message? \n");
    fgets( buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0; //strchr returns a pointer of the first occurance
    if ( strcmp( buffer, "exit") == 0){
      exit(1);
    }
    
    printf("Person to bother: [%s]\n", to_who);
    printf("Message to send: [%s]\n", buffer);

    i = 0;
    while (i<499){
      message[i] = 0;
      i++;
    }
    strcat(message, name);
    strcat(message, SPLIT);
    strcat(message, to_who);
    strcat(message, SPLIT);
    strcat(message, buffer);
    printf("Entire message is: [%s]\n", message);

    //write( to_server, buffer, sizeof(buffer) );
    //read( from_server, buffer, sizeof(buffer) );
    write( to_server, message, sizeof(message));
    printf("Message Sent: %s", message);
    read( from_server, buffer, sizeof(buffer) );
    printf("<client> received [%s]\n", buffer );
  }
  close (to_server);
  close(from_server);
  
}
