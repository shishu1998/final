#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>


static void sighandler(int signo){
  if(signo == SIGINT){
    printf("Server crash, oopsies doops\n");
    remove("pipe");
    exit(0);
  }
}

int handshake(int *from_player){

  int to_player;
  char buffer[100];

  mkfifo("pipe",0644);
  *from_player = open("pipe",O_RDONLY);
  remove("pipe");

  int f = fork();
  if(f == 0){
    read(*from_player,buffer,sizeof(buffer));
    printf("Handshake done\n");
    
    to_player = open(buffer,O_WRONLY);
    write(to_player,buffer,sizeof(buffer));
    return to_player;
  }
  else{
    return 0;
  }
}

char* process(char* string){
  strncpy(string,"Gone",sizeof(string));
}

void player_connection(int to_player,int from_player){
  char buffer[100];
  printf("before while loop\n");
  while(read(from_player,buffer,sizeof(buffer))){
    printf("server received %s\n",buffer);
    process(buffer);
    write(to_player,buffer,sizeof(buffer));
    strncpy(buffer,"",sizeof(buffer));
  }
}


int main(){

  signal(SIGINT,sighandler);
  
  int to_player;
  int from_player;
  char buffer[100];
  
  while(1){
    printf("waiting for players to connect\n");
    to_player = handshake(&from_player);

    if(to_player != 0){
      player_connection(to_player,from_player);
      close(to_player);
    }
  }
  
  return 0;
}
