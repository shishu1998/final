#include <stddef.h>
#include <netinet/in.h>
#include <netdb.h>

#include "hostname.h"

/*
 * Credit http://www.binarytides.com/hostname-to-ip-address-c-sockets-linux/
 */
int hostname_to_ip(char * hostname, struct in_addr** addr) {
  struct hostent *he = (void *)123456789;

  he = gethostbyname(hostname);
  if (he == NULL) {
    return -1;
  }

  *addr = (struct in_addr *) he->h_addr;

  return 0;
}
