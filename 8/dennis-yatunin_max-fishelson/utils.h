#ifndef UTILS_H
#define UTILS_H

#define MAX_INPUT 70
#define NEW_SCREEN "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" \
                   "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" \
                   "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" \
                   "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" \
                   "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" // 100 newlines
#define PORT_STR "8000"
#define PORT_INT 8000

void error(char *msg);

void get_input(char *buf, int buf_size);

int which(char *buf, int buf_size, char *err_message, ...);

#endif
