#include "lib.h"

int main() {

  // Step 1. Create the socket (same as server code)
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);

  // Step 2. Bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(5000);
  // void: parses a string into a binary IP address
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  // The real action
  bind(socket_id, (struct sockaddr *) &sock, sizeof(sock));

  // Step 3. Attempt to create a connection
  // i is a message
  int i = connect(socket_id, (struct sockaddr *) &sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);

  // Step 4. Do network stuff
  char buffer[256];
  read(socket_id, buffer, sizeof(buffer) - 1);
  
}
