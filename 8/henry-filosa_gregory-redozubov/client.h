#ifndef client
#define client

int connect_server();
/*======== Int connect_server() ==========
  Inputs:  None
  Returns: Int socket_id
  Attempts to connect to server, returns socket_id upon success
  ====================*/

void send_user();
/*======== Void send_user() ==========
  Inputs:  char *, char[], char[] pass, int socket_id
  Returns: Nothing
  Sends user's information to server
  ====================*/

#endif
