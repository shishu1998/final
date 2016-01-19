/*========== host_lookup.c ==========

find an ip address given a host name
=========================*/


#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char **argv) {

  char ip[256];
  char name[256];
  struct hostent *h;
  int i;

  if (argc != 2) {
    printf("Usage: host name\n");
    exit(0);
  }

  strcpy(name,argv[1]);
  h = gethostbyname(name);

  printf("\n%s's official name is : %s\n",name,h->h_name);
  printf("Alias list:\n");

  for (i=0; h->h_aliases[i] != NULL; i++) {
      printf("\t%s\n",h->h_aliases[i]);
  }

  printf("\n");
  inet_ntop(AF_INET,h->h_addr_list[0],ip,256);
  printf("Address: %s\n", inet_ntoa(h->h_addr_list[0]) );
  printf("ip: %s\n",ip);

}
