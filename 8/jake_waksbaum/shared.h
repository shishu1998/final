#ifndef SHARED_H
#define SHARED_H

#define PORT 5000

void check_errors(char * msg, int e);
void check_errors_except(char * msg, int e, int except);

#endif
