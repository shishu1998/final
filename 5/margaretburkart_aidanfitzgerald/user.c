#include "lib.h"

void destroy(user *u) {
  free(u->name);
  free(u->passwd);
  free(u);
}
