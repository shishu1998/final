#include "lib.h"

int main() {

  int socket_id, socket_client;

  // Step 1. Initialize the socket
  // Initialize a TCP socket (use AF_INET6 for a IPv6 socket or SOCK_DGRAM for a UDP socket)
  // Don’t worry about the 3rd argument
  if ( (socket_id = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Error creating socket");
    exit(1);
  }

  // Step 2. Bind the socket to an IP address and port
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  // htons() converts host byte order (usually little endian) to network byte order (big endian)
  // htons stands for host to network short
  listener.sin_port = htons(5000);
  // bind to all IP addresses that identify this machine (cf. 0.0.0.0)
  listener.sin_addr.s_addr = INADDR_ANY;
  // The real action - we SHOULD typecast (warning, not error)
  if (bind(socket_id, (struct sockaddr *) &listener, sizeof(listener)) == -1) {
    perror("Error binding to address");
    exit(1);
  }

  // Step 3. Set up the socket to listen (wait for clients)
  // 2nd parameter is deprecated (used to represent the max # of clients)
  // listen() does not block until a client initiates a connection
  if (listen(socket_id, 1) == -1) {
    perror("listen");
    exit(1);
  }

  while (9001) {
    // Step 4. Accept a client and assign the connection to a new file descriptor
    if ( (socket_client = accept(socket_id, NULL, NULL)) == -1) {
      perror("Error establishing a client connection");
      exit(1);
      //continue;
    }

    // Step 5. Do network stuff
    switch (fork()) {
    case -1:
      perror("Error forking");
      return 1;
      
    case 0:
      server_talk(socket_client);
      return 0;
      
    default:
      close(socket_client);
      continue;
    }
  }

}

void server_talk(int socket_client) {
  char *buffer;
  unsigned int size;

  // Session
  user *session = NULL;

  int r;

  while (6667) {

    // Read transmission size
    if ( (r = read(socket_client, &size, sizeof(int)) ) == -1) {
      perror("Error reading transmission size");
      exit(1);
    }
    else if (r < sizeof(int)) {
      fprintf(stderr, "Error reading transmission size: %d of %lu bytes read\n", r, sizeof(int));
      exit(1);
    }
    else {
      size = ntohl(size);
      printf("Reading up to %d bytes\n", size);
    }

    // Read transmission into dynamically allocated buffer
    buffer = malloc(size + 1);

#define die(status) do {    \
    user_freemem(session);  \
    close(socket_client);   \
    free(buffer); \
    exit(status); \
    } while (0)

    if ( (r = read(socket_client, buffer, size)) == -1) {
      perror("Error reading data from socket");
      exit(1);
    }
    else {
      buffer[r] = 0;
      printf("Read input: %10s\n", buffer);
    }

    // TODO: parse input
    if (strstart(buffer, "LOGIN")) {
      printf("Found LOGIN command\n");
      
      session = server_login(buffer);
      if (session) {
	sock_write(socket_client, "OK");
      }
      else if (errno == EACCES) {
	sock_write(socket_client, "FAIL\nIncorrect password");
	die(1);
      }
      else if (errno == ENOENT) {
	sock_write(socket_client, "FAIL\nNo such user");
	die(1);
      }
    }

    else if (strstart(buffer, "SETUP")) {
      session = server_acct_setup(buffer);
      if (session) {
	sock_write(socket_client, "OK");
      }
      else {
	sock_write(socket_client, "FAIL\nInvalid username");
	die(1);
      }
    }

    else if (strstart(buffer, "GET")) {
      // Retrieve one email
      
    }

    else if (strstart(buffer, "SEND")) {
      // Upload one email
      server_send(buffer, session);

      if (!errno) {
	sock_write(socket_client, "OK");
      }
      else {
	sock_write(socket_client, "FAIL\nCould not send email");
	die(1);
      }
    }

    else if (strstart(buffer, "LOGOUT")) {
      die(0);
    }

    // Done with transmission content
    free(buffer);

    // Reset errno
    errno = 0;
  }
  // END LOOP

  // Done with session
  user_freemem(session);
}

user *scan_userinfo(char *buffer) {
  printf("Entered scan_userinfo fn\n");
  
  user *u = malloc(sizeof(user));
  u->name = malloc(256);
  memset(u->name, 0, 256);
  u->passwd = malloc(256);
  memset(u->passwd, 0, 256);

  
  sscanf(buffer, "Username: %255s", u->name);
  sscanf(buffer, "Password: %255s", u->passwd);

  printf("%s / %s\n", u->name, u->passwd);

  printf("Created object\n");
  
  return u;
}

user *server_login(char *buffer) {
  user *u = scan_userinfo(buffer);

  // Validate login
  FILE *userfile = fopen("mail.d/users.csv", "r+");
  user *account = user_find(u->name, userfile);
  printf("user_find\n");
  fclose(userfile);
  printf("fclose\n");

  if (account) {
    if (strcmp(u->passwd, account->passwd) == 0) {
      // Username and password correct
      printf("Correct login\n");
      
      user_freemem(account);
      return u;
    }

    else {
      // Valid username, wrong password
      printf("Valid username, wrong password\n");
      
      user_freemem(u);
      user_freemem(account);
      errno = EACCES;
      return NULL;
    }
  }

  // No such user
  printf("No such user\n");
  
  user_freemem(u);
  errno = ENOENT;
  return NULL;
}

user *server_acct_setup(char *buffer) {
  user *u = scan_userinfo(buffer);

  // Create user in userfile
  FILE *userfile = fopen("mail.d/users.csv", "r+");
  user *clone = user_create(u->name, u->passwd, userfile);
  fclose(userfile);

  if (clone) {
    // Only free the struct, don't free the strings inside
    free(clone);

    // Make new folder for user
    char *folder = server_dir(u->name);
    if (mkdir(folder, 0744)) {
      perror("Error creating user directory");
      exit(1);
    }
    free(folder);

    return u;
  }

  free(u);

  return NULL;
}

void server_send(char *buffer, user *session) {
  // Skip past the newline
  char *content = strchr(buffer, '\n') + 1;

  // Get recipient info
  char *recipient = malloc(256 + 1);
  memset(recipient, 0, 256 + 1);
  sscanf(buffer, "To: %255s", recipient);

  // Append a slash, replacing the terminating null (there's another one right after it)
  recipient[255] = '/';
  
  // Initialize filename
  char *filename = server_dir(recipient);
  filename = realloc(filename, strlen(filename) + 9);

  // Done with sender ID buffer
  free(recipient);
  
  // Append hashcode to filename
  char *hashcode = hash_code(content);
  strcat(filename, hashcode);
  free(hashcode);

  // Write!
  FILE *mail = fopen(filename, "w");
  
  // Prepend sender information
  fprintf(mail, "From: %s\n", session->name);
  // Write mail content
  fputs(content, mail);
printf("Uploaded email to %s\n", filename);

  // Done with the file
  fclose(mail);

  // Done with the filename buffer
  free(filename);
}

void server_get(int client_socket, user *session) {
// Open the user's remote mailbox directory
char *dirname = server_dir(session->name);
DIR *dir = opendir(dirname);

// Read the first entry
 struct dirent *head;
 get_head: head = readdir(dir);
 if (head->d_type != DT_REG && head->d_type != DT_LNK) {
   goto get_head;
 }

 // Done with the directory
 closedir(dir);

 if (head) {
   // Read the file
   
 }
 else {
   // Report that no file was found
   sock_write("NONE");
   printf("User %s tried to find 
 }
}

/* /////I put these headers in so that the file would compile so that I could test LOGIN and SETUP */

/* char* server_dir(char* s){ */
/*   char* return_value = "hello"; */
/*   return return_value; */
/* } */

/* user* user_create(char* s1, char* s2, FILE* f){ */
/*   user* u; */
/*   return u; */
/* } */

/* user* user_find(char* s, FILE* f){ */
/*   user* u; */
/*   return u; */
/* } */

/* void user_freemem(user* u){ */

/* } */
