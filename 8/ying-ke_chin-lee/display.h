#include <unistd.h>
#include <errno.h>

#define browser "chromium-browser"

void display(Lot l) {
	char *cmds[2] = {browser, l.url};
	
	printf("cmds[0] = %s\n", cmds[0]);
	printf("cmds[1] = %s\n", cmds[1]);
	int f = fork();
	if (f == 0) {	
		//int fd1 = creat(cmds[0], 0644);
	        //dup2(fd1, 1);
        	//close(fd1);
		int num = execvp(browser, cmds);
		printf("error %d happened: %s\n", errno, strerror(errno));
		printf("num = %d\n", num);
		exit(0);
	} else {
		int status;
		wait(&status);
	}
}

/*
void display(char *link) {
	char *cmds[2] = {browser, link};

	int f = fork();
		if (f == 0) {	
			int fd1 = creat(cmds[0], 0644);
		        dup2(fd1, 1);
        		close(fd1);
			execvp(browser, cmds);
			exit(0);
		} else {
			int status;
			wait(&status);
		}
}

*/