
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>

int list_songs(int socket_client);
int handle_client(int socked_client);
int send_song(char * song_name, int socket_client);

int handle_client(int socket_client){
  char buf[64];
  while (  read(socket_client, buf, sizeof(buf))){
    char substr[1];
    memcpy (substr, &buf[0], 1);
    substr[1] = '\n';
    if (strcmp(substr, "l") == 0){
      //send song listings
      list_songs(socket_client);
    }
    if (strcmp(substr, "q") == 0){
      exit(0);
    }
    if (strcmp(substr, "p") == 0){
      send_song(buf, socket_client);
    }
  }

}

int send_song(char * user_input, int socket_client){
    char song[5242880]; //5 mb is enough right?
    char substr[3];
    memcpy(substr, &user_input[2], 3); //get 3 dig song num
    substr[3] = '\0';
    char song_title[64];
    //loop through songs and find corresponding title
    DIR * music_dir = opendir("music");
    struct dirent *file;
    int i = 0;
    while((file = readdir(music_dir))){
      if (i > 1){ //skip the . and ..
	char * test_title = file->d_name;
	char sub_title[3]
	memcpy(sub_title, test_title[0], 3);
	sub_title[3] = '\0';
	if (strcmp(sub_title, substr) == 0){
	  //this is the right song
	  memcpy(song_title, test_title, sizeof(test_title));
	  //^ buffer overflow possible here
	  song_title[64] = '\0';
	  break;
	}
      }
      i ++;
    }
    closedir(music_dir);
    
    //end song title loop

    int song_file = open(song_title, O_RDONLY);
    read(song_title, song, sizeof(song));
    write(socket_client, song, strlen(song) +1);
    printf("\n");
}

int list_songs(int socket_client){
  DIR * music_dir = opendir("music");
  struct dirent *file;
  char song_list[1024] = "";
  printf("orig song_listL [%s]\n", song_list);
  int i = 0;
  while((file = readdir(music_dir)) && strlen(song_list) < 1024){
    if (i > 1){ //skip the . and .. 
      printf("filename : [%s]\n", file->d_name);
      strcat(song_list, file->d_name);
      strcat(song_list, "\n");
      printf("new list: [%s]\n", song_list);
    }
    i ++;
  }
  closedir(music_dir);
  
  printf("total song list: \n[%s]\n ", song_list);
  

}

int main() {

  int socket_id, socket_client;
  
  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons(24601); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  listen( socket_id, 1 );
  printf("The jukebox server is up and running and waiting for clients to connect.\n");

   while (1) {
    socket_client = accept( socket_id, NULL, NULL );
    printf("<server> connected: %d\n", socket_client );
    int cpid = fork();
    if (cpid == 0){
      printf("in the client plce\n");
      handle_client(socket_client);
    }
   }
 
  return 0;
}
