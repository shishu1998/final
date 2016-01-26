#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void error(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void get_input(char *buf, int buf_size) {
	if (fgets(buf, buf_size, stdin) == NULL) {
		error("fgets");
	}
}

int which(char *buf, int buf_size, char *err_message, ...) {
	va_list options;
	char *option;
	int counter;
	while (1) {
		get_input(buf, buf_size);
		va_start(options, err_message);
		option = va_arg(options, char *);
		counter = 0;
		while(option != NULL) {
			if (strcmp(option, buf) == 0) {
				return counter;
			}
			option = va_arg(options, char *);
			counter++;
		}
		printf("%s\n", err_message);
	}
}