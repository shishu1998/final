
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "map.h"

#define PORT 5000
#define ID 0
#define UID_LENGTH 8

/**
 *  Removes the shared memory when the server is killed.
 */
static void clean_up_memory(int signo) {
  int e, sd, key;
  key = ftok("Makefile", ID);
  sd = shmget(key, MAP_MEMORY_SIZE, 0644);
  e = shmctl(sd, IPC_RMID, NULL);
  printf("Shared memory removed: %d\n", e);
  exit(0);
}

/**
 * Generates a UID of specified length.
 */
void generate_uid(char* buffer, int length) {
  int i;
  for (i = 0; i < length; ++i) {
    buffer[i] = (char) ((rand() % 26) + 97);
  }
  buffer[length] = '\0';
}

int main() {

  // Set up signal handler to clean up memory when we kill the server.
  signal(SIGINT, clean_up_memory);

  // Seed the random number generator.
  srand(time(NULL));

  // Character buffer for storing information from the clients.
  char buffer[256];
  // Socket information for data transfer to clients.
  int socket_id, socket_client;
  // Shared memory to maintain the state of the server between the server forks.
  int sd, key;
  char* map;

  // Create shared memory segment.
  key = ftok("Makefile", ID);
  sd = shmget(key, MAP_MEMORY_SIZE, 0644 | IPC_CREAT);
  printf("Shared memory created: %d\n", sd);

  // Initialize the map
  map = shmat(sd, 0, 0);
  init(map);
  generate_uid(buffer, UID_LENGTH);
  printf("%s\n", buffer);

  // Create the socket that will allow client connections.
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );

  // Bind to a specific port/address.
  struct sockaddr_in listener;
  listener.sin_family = AF_INET; // socket type IPv4
  listener.sin_port = htons(PORT); // port #
  listener.sin_addr.s_addr = INADDR_ANY; // bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));

  // Begin listening on the specified port.
  listen(socket_id, 1);
  printf("Listening on port %d\n", PORT);

  while (1) {
    // Wait for a client to join.
    socket_client = accept(socket_id, NULL, NULL);
    printf("Client connected: %d\n", socket_client );

    // Fork off a subprocess to handle the client's input.
    switch (fork()) {
    case -1:
      printf("Something broke!\n");
      return 0;

    case 0:
      // Child process handles input processing from the clients.
      map = shmat(sd, 0, 0);

      while (1) {
        recv(socket_client, buffer, sizeof(buffer), 0);
        strtok(buffer, "\n");
        send(socket_client, buffer, sizeof(buffer), 0);
      }

    default:
      // Parent process.
      close(socket_client);
    }
  }
  return 0;
}
