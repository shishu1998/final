#ifndef server
#define server

void setup();  
  /*======== void setup() ==========
  Inputs: none
  Returns: nothing
  Creates file to hold usernames & passwords (userlist),
   file for usernames that are logged in(logged) and main directory
  ====================*/

void startup();
/*======== void startup() ==========
  Inputs: none
  Returns: nothing
  Creates semaphore to guard access to the userlist and and logged
  ====================*/

int authenticate();
/*======== int authenticate() ==========
  Inputs: char name[],char password[]
  Returns: boolean
  Checks userlist for username and password
  Checks logged to see if user already logged in
  Returns 0 if correct combination not present or the user is already logged in
  ====================*/

int add_user();
/*======== int add_user() ==========
  Inputs: char name[],char password[]
  Returns: boolean
  Checks userlist to see if name is already taken
  Return 1 if name is available and appends name & password to userlist, 
   creates directory folders(mailboxes) for the new user.
  Returns 0 of name is taken
  ====================*/

#endif
