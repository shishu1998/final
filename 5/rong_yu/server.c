#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

char names[20][50];
char name[50];
int num_at = 0;


static void sighandler( int signo ){
  if (signo == SIGINT){
    printf("SIGINT accepted, proceeding to cleanup\n");
    remove("mario");
    exit(1);
  }
}

int server_handshake( int *from_client ){
  int to_client;
  char buffer[100];	
  mkfifo("mario", 0644);
  printf("<Server> has made the WKP 'Mario' \n");
  printf("<Server> is now waiting for a client\n");
  *from_client = open("mario", O_RDONLY); 
  //printf("<Server> is now waiting for the client to type something \n");
  read( *from_client, buffer, sizeof(buffer)) ;
  printf("<Server> connection request: [%s]\n", buffer ); //buffer is string null terminated pipe
  remove("mario");

  strcpy( names[num_at], buffer );
  num_at++;
  memset(name,0,strlen(name));
  strcpy( name, buffer);
  
  to_client = open( buffer, O_WRONLY);
  printf("Opened %s, about to write\n", buffer);
  sleep(1);
  write(to_client, "Hi, <Server> hereby acknowledges.\n", 40);
  printf("<Server> is now connected. Yay.\n\n\n");
 
  return to_client;

}

int scanThrough(){

  char buffer[200];
  //memset(name,0,strlen(name));
  int i = 0;
  while (i<num_at){
    memset(name,0,strlen(name));
    memset(buffer,0,strlen(buffer));
    //strcpy( name, names[i]);
    int fd = open(names[i], O_RDONLY);
    if (fd > 0){
      read( fd, buffer, sizeof(buffer) );
      printf("Name: %s\nMessage: %s\n\n", names[i], buffer);
    } else {
      printf("ERROR: %s\n", strerror(errno) );
    }
    close(fd);
    i++;
  }
  /*
  char muchStuff[100];
  int fd = open(muchStuff, O_RDONLY);
  read(fd, muchStuff, sizeof(muchStuff));
  
  int i = 0;
  while (buffer[i]){
    if (buffer[i] == '\n'){
      break;
    }
    i++;
  }*/
}

int main(){
  
  signal( SIGINT, sighandler );

  int to_client;
  int from_client;
  char buffer[200];
  int elder;
  char SPLIT[3] = "\n";
  //char SPLIT[18] = "010203040506070809";
  char parts[100];
  char message[200] = "";
  while (1){
    to_client = server_handshake( &from_client );
    
    elder = fork();
    //printf("Elder Number is: %d\n", elder);
    if (elder == 0){ // i.e. child
      while (1){
	memset(buffer,0,strlen(buffer));
	int stop = read( from_client, buffer, sizeof(buffer));
	if (stop<=3){
	  exit(0);
	}
	printf("Words sent from sub: %s\n", buffer);
	//printf( "<Server> received: %s\n", buffer);

	int fd = open( name, O_CREAT | O_WRONLY | O_TRUNC, 0644);

	//change the semaphore and or shared memory
	if (fd<0){
	  printf("Problem: %s\n", strerror(errno) );
	} else {
	  write( fd, buffer, sizeof(buffer) );
	}
	close(fd);

	int i = 0;
	while (buffer[i]){
	  if (buffer[i] == '\n'){
	    break;
	  }
	  i++;
	}
	strncpy(message, buffer, i);
	
	
	//printf("Name: %s\n", message);
	//#####################################################
	//sends this to the MS.
	//changes a semaphore
	//MS checks semaphores or shared memory, reverts it back to normal
	//MS then reads it.
	//MS sends back a response and changes semaphore
	//strcat(message, parts);
	//parts = strsep(&buffer, SPLIT); //to_who
	//strcat(message, parts);
	//parts = strsep(&buffer, SPLIT); //message
	//strcat(message, parts);
	
	/*
	
	while (buffer[i]){
	  ch = toupper(buffer[i]);
	  buffer[i] = ch;
	  i++;
	}
	buffer[i]= '?';
	buffer[i+1] = 0;
	*/

	write( to_client, message, sizeof(message));
      }
    } //if (i == 0)
    else{ //parent
      close (to_client);
      close (from_client);
      scanThrough();
      /*
      while (a<num_at){
	printf("Names: %s\n", names[a]);
	a++;
      }
      */
    }

  }

}
