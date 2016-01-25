#ifndef server
#define server

void setup();  
/*======== void setup() ==========
  Inputs: none
  Returns: nothing
  Creates file to hold usernames & passwords (userlist),
   file for usernames that are logged in(logged) and main directory
  Creates semaphores to guard userlist and logged
  ====================*/

void get_user();
/*======== int get_user() ==========
  Inputs: char * ans,char name[],char password[],int socket_client
  Returns: nothing
  Recieves username & password from client. ans determines whether new or old user
  ====================*/

void send_mail();
/*======== int send_mail() ==========
  Inputs: char name[],int socket_client
  Returns: nothing
  Checks if user has mail and sends mail to client if found
  ====================*/

void recieve_mail();
/*======== int recieve_mail() ==========
  Inputs: char name[],int socket_client
  Returns: nothing
  Recieves input from user. If target already has mail, append to end. Otherwise create a new file.
  ====================*/

int authenticate();
/*======== int authenticate() ==========
  Inputs: char name[],char password[]
  Returns: boolean
  Checks userlist for username and password
  Checks logged to see if user already logged in
  Takes into account semaphores.
  Returns 0 if correct combination not present or the user is already logged in.
  ====================*/

int add_user();
/*======== int add_user() ==========
  Inputs: char name[],char password[]
  Returns: boolean
  Checks userlist to see if name is already taken
  Return 1 if name is available and appends name & password to userlist, 
  Takes into account semaphores.
  Returns 0 of name is taken
  ====================*/

#endif
