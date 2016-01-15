#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "shared.h"

void check_errors(char * msg, int e) {
  if (e < 0) {
    perror(msg);
    exit(1);
  }
}

void check_errors_except(char * msg, int e, int except) {
  if (e < 0 && errno != except) {
      perror(msg);
      exit(1);
  }
}
