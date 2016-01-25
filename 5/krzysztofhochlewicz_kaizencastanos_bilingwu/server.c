//server side of making a TCP (with a 3 way handshake)

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int socket_id, socket_client;
    
    //create the socket
    socket_id = socket(AF_INET, SOCK_STREAM, 0);
    	      //AF_INET is the Ip address in IPv4, SOCK_STREAM is the stream of data packets going in, 0 is the default (lets your OS take care of stuff) 
    //bind to port/address
    struct sockaddr_in listener;
    listener.sin_family = AF_INET; //socket type IPv4
    listener.sin_port = htons(5000); //port #, htons(#) is a numberic conversion function. it is necessary because of the way a computer stores integers. the htons will take the way your computers way of handling bit order of storing integers and turn it into something that a NETWORK can use.
    listener.sin_addr.s_addr=INADDR_ANY; // bind to any incoming address
    bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
    
    listen(socket_id,1);//opens the socket up for a connection
    printf("<server> listening\n");
    
    socket_client = accept(socket_id, NULL, NULL);
    printf("<server> connected: %d\n", socket_client);
    
    write(socket_client, "hello", 6);
    
    return 0;
}