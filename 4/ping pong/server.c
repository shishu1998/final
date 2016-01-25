#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
  int socket_id, socket_client, connection_type, client_len;
  char *hosts = (char *)calloc(256, sizeof(char)); // Stores the IP address of the awaiting host, otherwise empty
  char *buffer = (char *)calloc(256, sizeof(char));
  struct sockaddr_in client_addr;

  while(true){
    socket_id = socket( AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in listener;
    listener.sin_family = AF_INET;
    listener.sin_port = htons(2143);
    listener.sin_addr.s_addr = INADDR_ANY;
    bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));

    listen(socket_id, 1);

    socket_client = accept(socket_id, (struct sockaddr *)&client_addr, &client_len);

    read(socket_client, buffer, sizeof(buffer));

    if(strcmp(buffer, "update_scores") == 0){
      connection_type = 0; // Request sent by client server at end of game about how the game went
    }

    if(strcmp(buffer, "new_game") == 0 && strlen(hosts) == 0){
      connection_type = 1; // Request sent by a client looking for a game, and there are no other previous client servers
    }

    if(strcmp(buffer, "new_game") == 0 && strlen(hosts) !=0 ){
      connection_type = 2; // Request sent by a client looking for a game, and there is a client server waiting for a game
    }

    else{
      connection_type = 3;
    }

    switch(connection_type){
      case 0:
        //Update scores in some file
        break;
      case 1:
        write(socket_client, "server", 7);
        break;
      case 2:
        write(socket_client, hosts, strlen(hosts)+1);
        hosts = (char *)calloc(256, sizeof(char));
        break;
      default:
        write(socket_client, "Error", 6);

    }
    close(socket_client);
    close(socket_id);
  }

  return 0;

}
