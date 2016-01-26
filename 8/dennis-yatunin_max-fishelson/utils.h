#ifndef UTILS_H
#define UTILS_H

#define MAX_INPUT 15

void error(char *msg);

int get_input(char *prompt, char *buf, int buf_size);

int select_input(char *prompt, char *buf, int buf_size, char *err_message, ...);

#endif
