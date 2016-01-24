
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include "jukebox.h"


void handle_client(int socket_client){
  char buf[64];

  while (  read(socket_client, buf, sizeof(buf))){
  	printf("analyzing input: %s\n", buf);
    char substr[2];
    memcpy (substr, &buf[0], 1);
    substr[1] = '\n';
    if (buf[0] == 'l'){
    	printf("Recieved 'l', listing songs\n");
   		list_songs(socket_client);
    }
    else if (buf[0] == 'q'){
		printf("Recieved 'q', quitting\n");   
    	exit(0);
    }
    else if (buf[0] == 'p'){
	    printf("Recieved 'p', playing a song\n");
	    send_song(buf, socket_client);
    }
    else{
    	printf("Sorry, could not comprehend that command\n");
    }
  }

}

int send_song(char * user_input, int socket_client){
    char song[5242880]; //5 mb is enough right? (no)
    char substr[4];
    memcpy(substr, &user_input[2], 3); //get 3 dig song num
    substr[3] = '\0';
    char song_title[64];
    DIR * music_dir = opendir("music");
    struct dirent *file;
    int i = 0;
    char * test_title;
    while((file = readdir(music_dir))){
    	if (i < 1){ 
			test_title = file->d_name;
			char sub_title[4];
			memcpy(sub_title, test_title, 3);
			sub_title[3] = '\0';
			if (strcmp(sub_title, substr) == 0){
			  	strcpy(song_title, test_title);
				//^ buffer overflow possible here
			  	song_title[63] = '\0';
			  	break;
			}
    	}
      i ++;
    }
    closedir(music_dir);
    char file_path[64] = "music/";
    strncat(file_path, song_title, sizeof(file_path) - 7);
    int song_file = open(file_path, O_RDONLY);
    if (song_file < 0){
    	return -1;
    }
    if (read(song_file, song, sizeof(song)) < 0){
    	return -1;
    }
    write(socket_client, song, strlen(song) +1);
    return 0;
}

int list_songs(int socket_client){
  DIR * music_dir = opendir("music");
  struct dirent *file;
  char song_list[1024] = "";
  int i = 0;
  while((file = readdir(music_dir)) && strlen(song_list) < 1024){
  	if (!(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0
  				|| strcmp(file->d_name, "README.md") == 0  ))
  	{   //above condition exludes ., .. and readme entries
      strcat(song_list, file->d_name);
      strcat(song_list, "\n");    
  	}
  }
  closedir(music_dir);
  write(socket_client, song_list, sizeof(song_list));
  printf("total song list: \n[%s]\n ", song_list);
  return 0;
}

int main() {
  int socket_id, socket_client;
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  struct sockaddr_in listener;
  listener.sin_family = AF_INET; 
  listener.sin_port = htons(24601); 
  listener.sin_addr.s_addr = INADDR_ANY; 
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  listen( socket_id, 1 );
  printf("The jukebox server is up and running and waiting for clients to connect.\n");
   while (1) {
    socket_client = accept( socket_id, NULL, NULL );
    int cpid = fork();
    if (cpid == 0){
      printf("Handling Client %d\n", socket_client);
      handle_client(socket_client);
    }
   }
  return 0;
}
