#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void parse(char * command){
  char * command_copy = malloc(strlen(command));
  strcpy(command_copy, command);
  command = strsep(&command, " ");
  if(command){ //play cmd goes here
    send(command_copy);
    play_song();
  }
  else{
    if(strcmp(command_copy, "q") == 0){
      send(command_copy);
      exit();
    }
    if(strcmp(command_copy, "l") == 0){
      send(command_copy);
      list_songs;
    }
  }
}


void send(char * message){
  if ((send(socket_id,message, strlen(message),0))== -1) {
    fprintf(stderr, "Failure Sending Message\n");
    close(socket_id);
    exit();
    }
  else {
    printf("Client:Message being sent: %s\n",message);

  }
}

void list_songs(){
  char * songs;
  int num_bytes;
  num_bytes = recv(socket_id, songs, sizeof(songs),0);
  printf("Client:Song List Received From Server -  %s\n", songs);
}

void play_song(){
  char * mp3;
  int num_bytes;
  num_bytes = recv(socket_id, server_response, sizeof(server_response),0);
  printf("Client:Message Received From Server -  %s\n", server_response);
  
  int song_file;
  song_file = open(now_playing.mp3, O_CREAT | O_RDWR , 0644);
  write(song_file, mp3, sizeof(mp3));
  //playsong code
  //  recieve mp3 file, save it to a temp file, play, delete it from the temp file
}

int main(int argc, char **argv) {
  
  int socket_id;
  char buffer[256];
  int i;
  
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
  
  //attempt a connection
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);
  char input[256];
  while(1){
    printf("type p followed by a songId to play that song(with a space) \ntype l to see a list of available songs \ntype q to quit the jukebox:\n");
    fgets(input, sizeof(input), stdin);
    parse(input);
    //recvfrom( socket_id, buffer, sizeof(buffer), 0, (struct sockaddr *)&sock, sizeof(sock) < 0);
    read(socket_id, buffer, sizeof(buffer));
    printf("<client> received: [%s]\n", buffer );
    strcpy(buffer, "");
  }
  return 0;
}
