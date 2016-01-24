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

// Simple hash algorithm: sum of bytes
char *hash_code(char *str) {
  int n = 0;
  while (*str) {
    n += *str;
    str++;
  }

  char *hex = malloc(9);
  sprintf(hex, "%8x", n);

  return hex;
}
