#include "lib.h"

int sock_write_n(int sock, char *str, int n) {
  int status;

  // Write four bytes for size
  n = htonl(n);
  status = write(sock, &n, sizeof(n));

  if (status < sizeof(n)) {
    
    return -2;
  }

  // Write the string itself
  status = write(sock, str, n);
  return status;
}

int sock_write(int sock, char *str) {
  return sock_write_n(sock, str, strlen(str));
}
