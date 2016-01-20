#include "lib.h"

char *client_dir(char *path) {
  char *base = "mail/";
  char *fullpath = malloc(sizeof(base) + strlen(path));
  strcpy(fullpath, base);
  strcat(fullpath, path);
  return fullpath;
}

char *server_dir(char *path) {
  char *base = "mail.d/";
  char *fullpath = malloc(sizeof(base) + strlen(path));
  strcpy(fullpath, base);
  strcat(fullpath, path);
  return fullpath;
}
