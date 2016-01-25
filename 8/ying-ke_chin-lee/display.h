#include <unistd.h>
#include <errno.h>

//#include "lot_struct.h"

#define browser "chromium-browser"

void bid();
void query();

void display(Lot l) {
	char *cmds[3] = {browser, l.url, NULL};
	
/*
	printf("cmds[0] = %s\n", cmds[0]);
	printf("cmds[1] = %s\n", cmds[1]);
*/
	int f = fork();
	if (f == 0) {	
		print(l);

		char ans[1];

		printf("View the work? y/n: ");
		scanf("%s", ans);
		if (strcmp(ans, "y") != 0) {
			printf("neq\n");
			exit(0);
		}

		// get input, if "y", then load browser. else, don't.
		int num = execvp(browser, cmds);
		if (num < 0) {
			printf("error %d happened: %s\n", errno, strerror(errno));
		}
		exit(0);
	} else {
		int status;
		wait(&status);
	}
//	bid();
}
