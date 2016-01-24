#ifndef JUKEBOX_H
#define JUKEBOX_H

int list_songs(int socket_client);
void handle_client(int socked_client);
int send_song(char * song_name, int socket_client);

#endif