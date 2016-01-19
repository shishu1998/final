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
  int size;

  // Session
  user *session;

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
      size = ntohi(size);
      printf("Reading up to %d bytes\n", size);
    }

    // Read transmission into dynamically allocated buffer
    buffer = malloc(size + 1);

    if ( (r = read(socket_client, buffer, size)) == -1) {
      perror("Error reading data from socket");
      exit(1);
    }
    else {
      buffer[r] = 0;
      printf("Read input: %s\n", buffer);
    }

    // TODO: parse input
    if (strstart(buffer, "LOGIN")) {
      session = server_login(buffer);
    }

    else if (strstart(buffer, "SETUP")) {
      session = server_acct_setup(buffer);
    }

    else if (strstart(buffer, "GET")) {
      // Retrieve one email
      
    }

    else if (strstart(buffer, "SEND")) {
      // Upload one email
      
    }

    else if (strstart(buffer, "LOGOUT")) {
      user_freemem(session);
      close(socket_client);
      free(buffer);
      exit(0);
    }

    // Done with transmission content
    free(buffer);

  }
  // END LOOP

  // Done with session
  user_freemem(session);
}

user *server_login(char *buffer) {
  user *u = malloc(sizeof(user));
  sscanf(buffer, "Username: %ms", &(u->name));
  sscanf(buffer, "Password: %ms", &(u->passwd));

  // Validate login
  FILE *userfile = fopen("mail.d/users.csv", "r+");
  user *account = user_find(u->name, userfile);
  fclose(userfile);

  if (account) {
    if (strcmp(u->passwd, account->passwd) == 0) {
      // Username and password correct
      user_freemem(account);
      return u;
    }

    else {
      // Valid username, wrong password
      user_freemem(u);
      user_freemem(account);
      errno = EACCES;
      return NULL;
    }
  }

  else {
    // No such user
    user_freemem(u);
    errno = ENOENT;
    return NULL;
  }
  
  return u;
}
