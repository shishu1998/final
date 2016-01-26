#include "client.h"

int main() {
  int socket_id;
  char buffer[256];
  int i;
  
  socket_id=socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sock;
  sock.sin_family=AF_INET;
  sock.sin_port = htons(24601);

  inet_aton("127.0.0.1", &(sock.sin_addr));
  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));

  i=connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);

  read(socket_id, buffer, sizeof(buffer));
  printf("<client> received: [%s]\n", buffer);

  return 0;
}
