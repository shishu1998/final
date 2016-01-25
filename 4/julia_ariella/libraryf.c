#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

static int SIZE = 100;

typedef struct {
  char *song;
  char *artist;
  char *genre;
} music;

void error(int n) {
  if (n < 0)
    printf("Error: %s\n", strerror(errno));
}

music *new_music() {
  music *node = malloc(sizeof(music));
  node->song = (char*)malloc(100);
  node->artist = (char*)malloc(100);
  node->genre = (char*)malloc(100);
  return node;
}

int retrieve(char *file, char *playlists[], music *library[][SIZE]) { //library is an array of arrays of music pieces

  //stores data from the file in the string data
  int fd = open(file, O_RDONLY);
  int size = lseek(fd, 0, SEEK_END);
  char *data = (char*)malloc(size);
  lseek(fd, 0, SEEK_SET);
  int check = read(fd, data, size);
  error(check);
  close(fd);

  //parses data using delimiter \n to separate into playlists
  char *pieces[500];
  char *hold = (char*)malloc(size);
  int i = 0;
  while (data) {
    hold = strsep(&data, "/");
    pieces[i] = hold;
    i++;
  }

  int num_playlists = i; //number of playlists
  
  //char *playlists[num_playlists];
  int num_songs;
  int count;

  for (i = 0; i < num_playlists; i++) {
    
    //parse each piece of pieces using delimiter : to get playlist names
    hold = strsep(&pieces[i], ":");
    playlists[i] = hold;
    int j = 0;
    while (pieces[i]) {
      hold = strsep(&pieces[i], ";");
      //parses song with , to make a music node
      music *meow = new_music();
      meow->song = strsep(&hold, ",");
      meow->artist = strsep(&hold, ",");
      meow->genre = hold;
      library[i][j] = meow; //add music node to list of songs
      j++;
    }
  }
  return num_playlists;
}

int add_song_playlist(music *library[][SIZE], int playlist, music *node) {
  int i;
  for (i = 0; i < SIZE; i++) {
    if (library[playlist][i] == NULL) {
      library[playlist][i] = node;
      return 1;
    }
    else if (strcmp(library[playlist][i]->song, node->song) == 0) 
      return 0;
  }
  return 2;
}

int add_playlist(char *playlists[], int num_playlists, char *playlist) {
  int i;
  for (i = 0; i < num_playlists; i++)
    if (strcmp(playlists[i], playlist) == 0) {
      printf("You already have a playlist with this name.\n");
      return num_playlists;
    }
  playlists[num_playlists] = playlist;
  num_playlists++;
  return num_playlists;
}

void add_song(music *library[][SIZE], char *playlists[], music *node, int playlist, int num_playlists) {
  add_song_playlist(library, 0, node); //adds song to library
  add_song_playlist(library, playlist, node); //adds to relevant playlist
}
  

//writes data back into file
void defenstrate(char *file, char *playlists[], int num_playlists, music *library[][SIZE]) { 

  //opens file
  int fd = open(file, O_CREAT|O_WRONLY, 0644);
  
  //write stuff
  int i;
  int j;
  int check;
  music *hold = new_music();
  for (i = 0; i < num_playlists; i++) {
    //each playlist
    check = write(fd, playlists[i], strlen(playlists[i]));
    error(check);
    check = write(fd, ":", 1);
    error(check);

    for (j = 0; j < SIZE; j++) {
      //each song
      hold = library[i][j];
      if (hold) {
	check = write(fd, hold->song, strlen(hold->song));
	error(check);
	check = write(fd, ",", 1);
	error(check);
	check = write(fd, hold->artist, strlen(hold->artist));
	error(check);
	check = write(fd, ",", 1);
	error(check);
	check = write(fd, hold->genre, strlen(hold->genre));
	error(check);
	if (library[i][j+1]) {
	  check = write(fd, ";", 1);
	  error(check);
	}
      }
    }
    if (i != num_playlists-1) {
      check = write(fd, "/", 1);
      error(check);
    }
  }
}


int account(int s1, char *uname) {
  int new;
  //char *uname = (char*)malloc(100);
  if (s1 == 1) { //create an account
    printf("What would you like your username to be?\n");
    scanf("%s", uname);

    int account = open("account.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (account == -1)
      printf("Error opening account: %s\n", strerror(errno));
    close(account);

    //read contents of file into a string
    char file_contents[100];
    long file_size;
    FILE *login1 = fopen("account.txt", "rb");
    fseek(login1, 0, SEEK_END);
    file_size = ftell(login1);
    rewind(login1);
    fread(file_contents, sizeof(char), file_size, login1);
    fclose(login1);
    
    char *slash1;
    slash1 = strstr(file_contents, uname);
    while (slash1 != NULL) {
      printf("This username was taken, please choose a new one.\n");
      scanf("%s", uname);
      slash1 = strstr(file_contents, uname);
    }

    account = open("account.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (account == -1)
      printf("Error opening account: %s\n", strerror(errno));
    
    int size = 0;
    while (uname[size] != 0)
      size++;
    
    int s = write(account, "/", 1);
    if (s < 0)
      printf("Error: %s\n", strerror(errno));
    
    int i = write(account, uname, size);
    if (i < 0)
      printf("Error: %s\n", strerror(errno));
    
    int c = write(account, ",", 1);
    if (c < 0)
      printf("Error: %s\n", strerror(errno));
    
    printf("Your username is: %s\nWhat would you like your password to be?\n", uname);
    char pword[30];
    scanf("%s", pword);
    
    int size2 = 0;
    while (pword[size2] != 0)
      size2++;
    
    int j = write(account, &pword, size2);
    if (j < 0)
      printf("Error: %s\n", strerror(errno));
    
    uname[size] = '.';
    uname[size+1] = 't';
    uname[size+2] = 'x';
    uname[size+3] = 't';
    
    new = open(uname, O_CREAT | O_WRONLY | O_APPEND, 0644);
    int check = write(new, "library", 7);
    close(new);
    
    close(account);
    return 1;
  }
  
  if (s1 == 2) { //log in to account
    
    printf("What is your username?\n");
    scanf("%s", uname);
    
    printf("What is your password?\n");
    char pword1[30];
    scanf("%s", pword1);
    
    //read contents of file into a string
    char file_contents[100];
    long file_size;
    FILE *login = fopen("account.txt", "rb");
    fseek(login, 0, SEEK_END);
    file_size = ftell(login);
    rewind(login);
    fread(file_contents, sizeof(char), file_size, login);
    fclose(login);

    int size3 = 0;
    int keep = 0;
    while (uname[size3] != 0) {
      size3++;
      keep = size3;
    }
    
    int elk = 0;
    while(pword1[elk] != 0) {
      elk++;
      size3++;
    }
    
    char bear[size3];
    int porcupine = 0;
    bear[porcupine] = '/';
    porcupine++;
    elk = 0;
    while (uname[elk] != 0) {
      bear[porcupine] = uname[elk];
      elk++;
      porcupine++;
    }
    bear[porcupine] = ',';
    porcupine++;
    elk = 0;
    while (pword1[elk] != 0) {
      bear[porcupine] = pword1[elk];
      porcupine++;
      elk++;
    }
    bear[size3] = 0;

    char *slash;
    slash = strstr(file_contents, bear);
    if (slash == NULL) {
      printf("Login failed.\n");
      return 0;
    }
    if (slash != NULL) {
      printf("Login succeeded!\n");
      
      uname[keep] = '.';
      uname[keep+1] = 't';
      uname[keep+2] = 'x';
      uname[keep+3] = 't';
      
      int new = open(uname, O_RDONLY | O_WRONLY | O_APPEND, 0644);
      close(new);
      return 1;
    }
  }
  else {
    printf("You have to choose 1 or 2.\n");
    return 0;
  }
  return 2;
}

char* shuffle( music *library[][SIZE], char* playlists[], int z, int num_playlists) { 
  srand(time(NULL));
  int r = rand();
  int j = 0;
  
  int i;
  int index;
  index = z;
  for (i = 0; i < SIZE; i++) {
    music *node = library[index][i];
    if (node) {
      j++;
    }
  }
  r = r%j;
  char *shuffled = library[index][r] -> song;
  return shuffled;
}

void display(music *library[][SIZE], char *playlists[], int playlist, int num_playlists) {
  int i;
  for (i = 0; i < SIZE; i++) {
    music *node = library[playlist][i];
    if (node)
      printf("Song: %s   Artist: %s    Genre: %s\n", node->song, node->artist, node->genre);
  }
}

void list_playlist(char *playlists[], int num_playlists) {
  int i;
  for (i = 0; i < num_playlists; i++) 
    printf("%d) %s\n", i+1, playlists[i]);
}

void suggest(music *library[][SIZE], char *name) {
  int i;
  music *node = new_music();
  char *genre = (char*)malloc(30);
  for (i = 0; i < SIZE; i++) {
    node = library[0][i];
    if (node && (strcmp(node->song, name) == 0)) 
      genre = node->genre;
  }

  music *list[SIZE];

  int count = 0;
  for (i = 0; i < SIZE; i++) {
    node = library[0][i];
    if (node && (strcmp(node->genre, genre) == 0)){
      list[count] = new_music();
      list[count] = node;
      count++;
    }
  }
  if (count == 1)
    printf("Suggested song: %s by %s\n", library[0][0]->song, library[0][0]->artist);
  else {
    srand(time(NULL));
    int num = rand() % count;
    printf("%d\n", num);
    printf("Suggested song: %s by %s\n", list[num]->song, list[num]->artist);
  }
}

char* playsong() {
  printf("What song would you like to play?\n");
  char song[30];
  scanf("%s", song);
  char *hold = (char*)malloc(30);
  strcpy(hold, song);
  
  //add .wav
  int size = 0;
  while (song[size] != 0)
    size++;
  song[size] = '.';
  song[size+1] = 'w';
  song[size+2] = 'a';
  song[size+3] = 'v';
  song[size+4] = 0;
  
  int p;
  p = fork();
  if (p != 0) {
    int status = 1;
    wait(&status);
    return hold;
  }
  else {
    execlp("afplay", "afplay", song, (char*)NULL);
  }
  return 0;
}

void playshuffle(char* name) {  
  strcat(name, ".wav");
  int p;
  p = fork();
  if (p != 0) {
    int status = 1;
    wait(&status);
  }
  else {
    execlp("afplay", "afplay", name, (char*)NULL);
  }
}

music* make_node(char* song_name, char* artist_name, char* genre_name) {
  music* num = (music*)malloc(sizeof(music));
  num = new_music();
  num -> song = song_name;
  num -> artist = artist_name;
  num -> genre = genre_name;
  return num;
}

char *playlist_name(char *playlists[], int playlist) {
  return playlists[playlist];
}
