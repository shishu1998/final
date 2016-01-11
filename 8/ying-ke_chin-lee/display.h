#include <unistd.h>
#include <errno.h>

//#include "lot_struct.h"

#define browser "chromium-browser"
void bid();

void display(Lot l) {
	char *cmds[3] = {browser, l.url, NULL};
	
	printf("cmds[0] = %s\n", cmds[0]);
	printf("cmds[1] = %s\n", cmds[1]);
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
	bid();
}

void bid() {
	int status;
	char ans[1];
	printf("Bid on this work? (y/n)\n");
	scanf("%s", ans);
	if (strcmp(ans, "y") != 0) {
		// do nothing.
		printf("Chose to do nothing.\n");
		exit(0);
	} else {
		//open bid
		printf("why does nothing happen\n");
		int f = fork();
		if (f == 0) {
			char *creat[3] = {"./control", "-c", NULL};
			int f0 = fork();
			if (f0 == 0) {
				execvp(creat[0], creat);
				exit(0);
			}
			else {
				wait(&status);
			}
			
			// start the writing program, which will write bids
			char *cmds[2] = {"./writing", NULL};
			int f1 = fork();
			if (f1 == 0) {
				execvp(cmds[0], cmds);
				exit(0);
			} else {
				wait(&status);
			}

			// close bid info
			char *remv[3] = {"./control", "-r", NULL};
			int f2 = fork();
			if (f2 == 0) {
				execvp(remv[0], remv);
				exit(0);
			} else {
				wait(&status);
			}
		} else {
			wait(&status);
		}
	}
}

/*
void display(char *link) {
	char *cmds[2] = {browser, link};

	int f = fork();
	if (f == 0) {	
//		int fd1 = creat(cmds[0], 0644);
//	        dup2(fd1, 1);
//     		close(fd1);
		execvp(browser, cmds);
		exit(0);
	} else {
		int status;
		wait(&status);
	}
}

*/
