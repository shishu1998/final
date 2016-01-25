#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include "libraryf.h"


int main() {
  char* hold = malloc(100);
  printf("Hello, and welcome to iTerminal!\n\nWould you like to: \n1) Create an account \n2) Log in to your account \nChoose 1 or 2\n");
  int s1;
  scanf("%d", &s1);
  char *file = (char*)malloc(100);
  int acc = account(s1, file);
  while (acc  == 0) {
    printf("Hello, and welcome to iTerminal!\n\nWould you like to: \n1) Create an account \n2) Log in to your account \nChoose 1 or 2\n");
    scanf("%d", &s1);
    acc = account(s1, file);
  }
  if (acc != 0) {
    //printf("praying: %i\n", account(s1, file));
    printf("%s\n", file);
    char *playlists[SIZE];
    music *library[SIZE][SIZE];
    int num_playlists = retrieve(file, playlists, library);
    
    if (s1 == 1) {
      music *node = new_music();
      node->song = "Big_Yellow_Taxi";
      node->artist = "Counting_Crows";
      node->genre = "Folk_rock";
      
      music *node1 = new_music();
      node1->song = "Breathe_Again";
      node1->artist = "Sara_Bareilles";
      node1->genre = "Pop";

      music *node2 = new_music();
      node2->song = "Fake_Plastic_Trees";
      node2->artist = "Radiohead";
      node2->genre = "Alternative_rock";

      music *node3 = new_music();
      node3->song = "Let_It_Be";
      node3->artist = "The_Beatles";
      node3->genre = "Pop";
      
      num_playlists = add_playlist(playlists, num_playlists, "CS_songs");
      add_song(library, playlists, node, 1, num_playlists);
      add_song(library, playlists, node1, 0, num_playlists);
      add_song(library, playlists, node2, 1, num_playlists);
      add_song(library, playlists, node3, 1, num_playlists);
      defenstrate(file, playlists, num_playlists, library);
    }
    
    int i = 1; //i = playlist index + 1
    while (i) {
      int real = i - 1;
      printf("You are currently in your %s playlist. What would you like to do? \n1) See the songs in the %s playlist \n2) Play a specific song \n3) Play a random song \n4) Add a song \n5) Make a playlist \n6) Go to a playlist. \n7) Log out\n\n\n*Always use underscores instead of spaces, please!*\n", playlist_name(playlists,real), playlist_name(playlists,real));
      int choice;
      scanf("%d", &choice);
      if (choice == 1) {
	display(library, playlists, real, num_playlists);
      }
      if (choice == 2) {
	char *name = (char*)malloc(30);
	strcpy(name, playsong());
	if (real == 0)
	  suggest(library, name);
      }
      if (choice == 3) {
	char* sname = shuffle(library, playlists, real, num_playlists);
	char name[20];
	strcpy(name, sname);
	printf("Playing: %s\n", name);
	playshuffle(name);
      }
      if (choice == 4) {
	printf("In addition to filling out the information below, in order to play the songs you are adding to this libarary/playlist, you need to download the songs as .wav files and put them in the same directory as this program. In addition, you must name them the same thing as you say the song's name is (i.e. if you write the song's name is Here_Comes_The_Sun, the file should be: Here_Comes_The_Sun.wav).\n\n");
	printf("What is the song's name?\n");
	char *song_name = (char*)malloc(15);
	scanf("%s", song_name);
	printf("What is the song's artist?\n");
	char *song_artist = (char*)malloc(15);
	scanf("%s", song_artist);
	printf("What is thes song's genre?\n");
	char *song_genre = (char*)malloc(15);
	scanf("%s", song_genre);
	char* name = song_name;
	add_song(library, playlists, make_node(song_name, song_artist, song_genre), real, num_playlists);
	defenstrate(file, playlists, num_playlists, library);
      }
      if (choice == 5) {
	printf("What would you like the playlist to be called?\n");
	char playlist_name[15];
	scanf("%s", playlist_name);
	num_playlists = add_playlist(playlists, num_playlists, playlist_name);
	defenstrate(file, playlists, num_playlists, library);
      }
      if (choice == 6) { 
	list_playlist(playlists, num_playlists);
	printf("What playlist would you like to go to?\n");
	int p;
	scanf("%d", &p);
	i = p;
      }
      if (choice == 7) {
	i = 0;
	defenstrate(file, playlists, num_playlists, library);
      }
      if ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5) && (choice != 6) && (choice != 7)) {
	printf("You've gotta type in a number, 1 - 7. Try again.\n");
      }      
    }  
  }
  return 0;
}

