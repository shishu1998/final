#include "lib.h"

int main() {

  int socket_id, socket_client;

  // Step 1. Initialize the socket
  // Initialize a TCP socket (use AF_INET6 for a IPv6 socket or SOCK_DGRAM for a UDP socket)
  // Don’t worry about the 3rd argument
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  // Step 2. Bind the socket to an IP address and port
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  // htons() converts host byte order (usually little endian) to network byte order (big endian)
  // htons stands for host to network short
  listener.sin_port = htons(5000);
  // bind to all IP addresses that identify this machine (cf. 0.0.0.0)
  listener.sin_addr.s_addr = INADDR_ANY;
  // The real action - we SHOULD typecast (warning, not error)
  bind(socket_id, (struct sockaddr *) &listener, sizeof(listener));

  // Step 3. Set up the socket to listen (wait for clients)
  // 2nd parameter is deprecated (used to represent the max # of clients)
  // listen() does not block until a client initiates a connection
  listen(socket_id, 1);

  while (420) {
    // Step 4. Accept a client and assign the connection to a new file descriptor
    socket_client = accept(socket_id, NULL, NULL);

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
