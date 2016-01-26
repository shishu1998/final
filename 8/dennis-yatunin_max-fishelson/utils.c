#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void error(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int get_input(char *prompt, char *buf, int buf_size) {
	// Make sure the prompt is displayed even if it doesn't end in
	// a '\n' character.
	if (prompt != NULL) {
		printf("%s", prompt);
		fflush(stdout);
	}

	// Return -1 if the user only entered "\n".
	*buf = getchar();
	if (*buf == '\n') {
		return -1;
	}

	int counter = 1;
	while (counter < buf_size - 1 && (buf[counter] = getchar()) != '\n') {
		counter++;
	}

	// Return -1 if the user entered more than buf_size - 1 characters
	// before  the '\n', and also flush the input stream so the excess
	// text does not affect the next request for user input.
	if (counter == buf_size - 1) {
		fflush(stdin);
		return -1;
	}

	// End the buffer with a '\0' character and return 0.
	buf[counter] = '\0';
	return 0;
}

int select_input(
	char *prompt, char *buf, int buf_size, char *err_message, ...
	) {
	printf("%s", prompt);

	va_list options;
	char *option;
	int counter;

	while (1) {
		get_input(NULL, buf, buf_size);
		va_start(options, err_message);
		option = va_arg(options, char *);
		counter = 0;

		while(option != NULL) {
			if (strcasecmp(option, buf) == 0) {
				return counter;
			}
			option = va_arg(options, char *);
			counter++;
		}

		printf("%s\n", err_message);
	}
}
