#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Network libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// File system libraries
//#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include <errno.h>
#include <string.h>

#include <sys/stat.h>

#define strstart(haystack, needle) strncmp(haystack, needle, strlen(needle)) == 0

typedef struct {char *name; char *passwd;} user;

// Client code
void client_talk(int);

// Server code
void server_talk(int);
user *server_login(char*);
user *server_acct_setup(char*);
void server_send(char*, user*);
void server_get(int, user*);

// User operations
user *user_find(char*, FILE*);
user *user_create(char*, char*, FILE*);
void user_freemem(user*);

// Common network stuff
int sock_write_n(int, char*, int);
int sock_write(int, char*);

// Common filename stuff
char *client_dir(char*);
char *server_dir(char*);
char *hash_code(char*);

////Functions in client.c
//String function
void strip_add(char*, char*);

//File navigation functions
void change_location(char*); //moves between subfolders
void execute(char*,int); //executes user's command
void take_directions(int); //prompts user for a command, then reads it
void my_ls(); //lists contents of current location
void enter_mail(int); //starting screen for file navigation

//Authentication functions
void sign_in(int);
void sign_up(int);
void choose_username(char*, char*);
void choose_password(char*, char*, char*, int);
void check_for_account(char*, int);

