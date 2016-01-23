#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "values.h"
#include "client.h"

//Needs to be global for signandler to work
int socket_id;

static void sighandler(int signo){
  int error;
  if (signo==SIGPIPE){
    error=close(socket_id);
    if (error == -1)
	perror("Error closing client socket\n");
    printf("Server disconnected, client exiting\n");
    exit(42);
  }
  if (signo==SIGINT){
    write(socket_id,&kill_num,4);
    printf("Closing socket\n");
    error=close(socket_id);
    if (error == -1)
      perror("Error closing socket\n");
    printf("Socket closed\n");
    exit(42);
  }
}
 
int connect_server(){
  struct sockaddr_in sock; 
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  sock.sin_family = AF_INET; //socket type to IPv4
  sock.sin_port = htons(PORTNUM); //port # 
  //convert IP address to correct format and insert into sock.sin_addr
  inet_aton( "127.0.0.1", &(sock.sin_addr) ); 
  //insert the socket info stuff into the file thing
  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  //attempt a connection. Will return -1and set errno if failed
  int error = connect( socket_id, (struct sockaddr *)&sock, sizeof(sock));
  if (error==-1){
    printf("Error connecting to server: %s\n",strerror(errno));
    exit(42);
  }
  return socket_id;
}

void send_user(char * ans,char name[], char pass[], int socket_id){
  int error=write(socket_id,ans,1);
  if (error==-1){
    printf("Error sending ANS to server: %s\n",strerror(errno));
    exit(42);
  }
  error=write(socket_id,name,NAME_LEN);
  if (error==-1){
    printf("Error sending name to server: %s\n",strerror(errno));
    exit(42);
  }
  error=write(socket_id,pass,PASS_LEN);
  if (error==-1){
    printf("Error sending password to server: %s\n",strerror(errno));
    exit(42);
  }
}

int main(int argc, char *argv[]){
  signal(SIGINT,sighandler);
  char ans;
  char name[NAME_LEN];
  char password[PASS_LEN];
   while (ans!='1' && ans!='2'){
     printf("Welcome to DW-NET\nAre you:\n1-Logging in\n2-Creating a new account\n");
     fgets(&ans,3,stdin);
   }
   if (ans=='2')
     printf("When creating you new account please keep in mind these restrictions:\n\tMaximum username length: %d characters\n\tMaximum password length: %d characters\n",NAME_LEN-1,PASS_LEN-1);
   printf("\nUsername:\n");
   fgets(name,NAME_LEN,stdin);
   printf("\nPassword:\n");
   fgets(password,PASS_LEN,stdin);
   strtok(name,"\n");
   strtok(password,"\n");
   printf("Username: =%s= Password: =%s=\n",name,password);
   //connect to server
   socket_id=connect_server();
   if (ans=='1'){
     send_user(&ans,name,password,socket_id);
     //verify correct name and password
     //if incorrect disconnect
     //If correct, recieve any backlog of msgs,files,commands
   }
   if (ans=='2'){
     send_user(&ans,name,password,socket_id);
     //See if uername available
     //If not available, ask user to create a different name. Resend that
   }       
   //Begin standard operation
   int size;
   int size_out;
   int error;
   char target[NAME_LEN];
   char buf_out[MAX_MSG];
   while (1==1){
     error=read(socket_id,&size,sizeof(size));
     if (error == -1)
       perror("Error getting size\n");
     if (size){
       char buf_in[size];
       read(socket_id,buf_in,size);
       printf("Your messages: \n%s",buf_in);
     }
     printf("Who do you want to message?\n");
     fgets(target,NAME_LEN,stdin);
     strtok(target,"\n");
     printf("Message contents:\n");
     fgets(buf_out,MAX_MSG,stdin);
     strtok(buf_out,"\n");
     size_out=strlen(target)+1;
     write(socket_id,&size_out,4);
     write(socket_id,target,size_out);
     size_out=strlen(buf_out)+1;
     write(socket_id,&size_out,4);
     write(socket_id,buf_out,size_out);
     printf("Message sent: %s\n",buf_out);
   }
}
