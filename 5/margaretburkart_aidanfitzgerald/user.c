#include "lib.h"

user *user_find(char *name) {
  // Begin working with file
  char *ufname = server_dir("users.csv");

  // Get file size
  struct stat ufinfo;
  if (stat(ufname, &ufinfo)) return NULL;
  int ufsize = ufinfo.st_size;

  // Read file into buffer
  FILE *uf = fopen(ufname, "r");
  char *ufbuffer = malloc(ufsize + 1);
  if (!fgets(ufbuffer, ufsize + 1, uf)) return NULL;
  fclose(uf);

  // Done working with file
  free(ufname);

  // Parse tokens - lines - and find the line that contains the correct username
  char *token = strtok(ufbuffer, "\n");
  while (token && !strstart(token, name)) {
    token = strtok(NULL, "\n");
  }

  if (token) {
    // Parse at the first comma
    token = strtok(token, ",");
    // Get the string after the comma - that's the password
    token = strtok(NULL, ",");

    // malloc and strcpy ensures that passwd is freeable later
    char *passwd = malloc(strlen(token) + 1);
    strcpy(passwd, token);

    // Done with the buffer
    free(ufbuffer);
    
    // User found - indicated by presence of password field
    user *found = malloc(sizeof(user));
    found->name = name;
    found->passwd = passwd;
    return found;
  }

  else {
    // User not found
    free(ufbuffer);
    return NULL;
  }
  
}

// TODO make directories
user *user_create(char *name, char *passwd) {  
  user *u;

  // Return if user already exists
  if ( (u = user_find(name)) ) {
    // Don't free u->name
    free(u->passwd);
    free(u);
    
    errno = EEXIST;
    return NULL;
  }

  // Add user to flat file
  char *ufname = server_dir("users.csv");
  FILE *uf = fopen(ufname, "r");
  fseek(uf, 0, SEEK_END);
  int status = fprintf(uf, "%s,%s\n", name, passwd);

  // Clean up
  fclose(uf);
  free(ufname);

  // Check if fprintf worked
  if (status > 0) {
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
