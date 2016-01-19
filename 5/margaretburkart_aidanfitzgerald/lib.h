#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Network libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// File system libraries
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <string.h>

#define strstart(haystack, needle) strncmp(haystack, needle, strlen(needle)) == 0

typedef struct {char *name; char *passwd;} user;

// Client code
void client_talk(int);

// Server code
void server_talk(int);
user *server_login(char*);

// User operations
user *user_find(char*, FILE*);
user *user_create(char*, char*, FILE*);
void user_freemem(user*);
