#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "values.h"
 
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

int main(int argc, char *argv[])
{
   char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
   char name[NAME_LEN];
   char password[PASS_LEN];

   char ans;
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
   int socket_id=connect_server();
   if (ans=='1'){
     //verify correct name and password
     //if incorrect disconnect
     //If correct, recieve any backlog of msgs,files,commands
   }
   if (ans=='2'){
     //See if uername available
     //If not available, ask user to create a different name. Resend that
   }       
   //Begin standard operation
   //Create socket
   char buf[6];
   read(socket_id,&buf,6);
   printf("Message recieved: %s\n",buf);
   close(socket_id);
   /*
   len = recv(mysocket, buffer, MAXRCVLEN, 0);
   // We have to null terminate the received data ourselves 
   buffer[len] = '\0';
   printf("Received %s (%d bytes).\n", buffer, len);
   close(mysocket);
   return EXIT_SUCCESS;
   */
}
