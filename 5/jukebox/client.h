#ifndef CLIENT_H
#define CLIENT_H

void parse(char * command, int socket_id);
void send_to_server(char * message, int socket_id);
void list_songs(int socket_id);
void play_song(int socket_id);

#endif
