#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "values.h"
 

int connect_server(int mysocket){
  struct sockaddr_in dest; 
  //zero the struct 
  memset(&dest, 0, sizeof(dest));               
  dest.sin_family = AF_INET;
  //set destination IP number - localhost, 127.0.0.1
  dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  //set destination port number
  dest.sin_port = htons(PORTNUM);               
  connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
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
   printf("\nUsername:\n");
   fgets(password,PASS_LEN,stdin);
   strtok(name,"\n");
   strtok(password,"\n");
   printf("Username: =%s= Password: =%s=\n",name,password);
   //connect to server
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
   int mysocket = socket(AF_INET, SOCK_STREAM, 0);
   //Connect to server
   connect_server(mysocket);

   /*
   len = recv(mysocket, buffer, MAXRCVLEN, 0);
   // We have to null terminate the received data ourselves 
   buffer[len] = '\0';
   printf("Received %s (%d bytes).\n", buffer, len);
   close(mysocket);
   return EXIT_SUCCESS;
   */
}
