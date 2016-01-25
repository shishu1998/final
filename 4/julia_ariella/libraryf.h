static int SIZE = 100;


typedef struct {
  char *song;
  char *artist;
  char *genre;
} music;


void error(int n);
music *new_music();
int retrieve(char *file, char *playlists[], music *library[][SIZE]);
int add_song_playlist(music *library[][SIZE], int playlist, music *node);
int add_playlist(char *playlists[], int num_playlists, char *playlist);
void add_song(music *library[][SIZE], char *playlists[], music *node, int playlist, int num_playlists);
void defenstrate(char *file, char *playlists[], int num_playlists, music *library[][SIZE]);
int account(int s1, char *uname);
char* shuffle( music *library[][SIZE], char* playlists[], int z, int num_playlists);
void display(music *library[][SIZE], char *playlists[], int playlist, int num_playlists);
void list_playlist(char *playlists[], int num_playlists);
void suggest(music *library[][SIZE], char *name);
char* playsong();
void playshuffle(char* name);
music* make_node(char* song_name, char* artist_name, char* genre_name);
char *playlist_name(char *playlists[], int playlist);  
