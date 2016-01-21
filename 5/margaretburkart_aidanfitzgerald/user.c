#include "lib.h"

user *user_find(char *name, FILE *userfile) {
  char *passwd;

  // Generate format string
  char *regex = malloc(strlen(name) + 5);
  strcpy(regex, name);
  strcat(regex, ",%ms");

  // Search for user and password
  rewind(userfile);
  if (fscanf(userfile, regex, &passwd) > 0) {
    // User found - indicated by presence of password field
    user *found = malloc(sizeof(user));
    found->name = name;
    found->passwd = passwd;

    free(regex);
    return found;
  }
  else {
    // User not found
    free(regex);
    return NULL;
  }

}

// TODO make directories
user *user_create(char *name, char *passwd, FILE *userfile) {
  user *u;

  // Return if user already exists
  if ( (u = user_find(name, userfile)) ) {
    // Don't free u->name
    free(u->passwd);
    free(u);
    
    errno = EEXIST;
    return NULL;
  }

  // Add user to flat file
  fseek(userfile, 0, SEEK_END);
  if ( fprintf(userfile, "%s,%s\n", name, passwd) > 0) {
    u = malloc(sizeof(user));
    u->name = name;
    u->passwd = passwd;
    return u;
  }
  else {
    return NULL;
  }
}

void user_freemem(user *u) {
  free(u->name);
  free(u->passwd);
  free(u);
}
