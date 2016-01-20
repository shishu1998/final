#ifndef LEN_PREFIX_H
#define LEN_PREFIX_H

#include <sys/types.h>

int len_prefix_write(int filed, void * message, size_t len);
int len_prefix_read(int filed, void ** message);

#endif
