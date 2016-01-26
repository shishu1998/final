#ifndef HOSTNAME_H
#define HOSTNAME_H

#include <netinet/in.h>

int hostname_to_ip(char * hostname, struct in_addr** addr);

#endif
