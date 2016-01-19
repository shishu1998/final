#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "len_prefix.h"

int len_prefix_write(int filed, void * message, size_t len) {
  int e;

  e = write(filed, &len, sizeof(len));
  if (e < 0) return e;

  e = write(filed, message, len);

  return e;
}

int len_prefix_read(int filed, void ** message) {
  int e;
  size_t message_len;

  e = read(filed, &message_len, sizeof(message_len));
  if (e < 0) return e;

  if (message_len ==  0) {
    return -1;
  }

  *message = realloc(*message, message_len);

  e = read(filed, *message, message_len);

  return e;
}
