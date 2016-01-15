#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>
#include <string.h>

#define strstart(haystack, needle) strncmp(haystack, needle, strlen(needle)) == 0

typedef struct {char *name; char *passwd;} user;




void client_talk(int);

void server_talk(int);
user *server_login(char*);

void user_delete(user*);
