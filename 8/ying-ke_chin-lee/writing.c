#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

char *fname = "bids.txt"; // will have to make one bid file per item later on

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

struct sembuf sb;

void prev_line() {
	printf("The previous line was:\n");
	FILE *fp = fopen(fname, "r");
	if (fp != NULL) {
		char line[1000];

		while (fgets(line, sizeof(line), fp) != NULL) {
			//printf("This line is %s\n", line);
		}
		printf("%s\n", line);
	} else {
		printf("Could not open\n");
		exit(1);
	}
}

int main() {
	int semkey = ftok("writing.c", 'a');
	int semid = semget(semkey, 1, IPC_CREAT|0666);

	sb.sem_flg = SEM_UNDO;
	sb.sem_op = -1;
	sb.sem_num = 0;
	//semop(semid, &sb, 1);

	prev_line();
	printf("\nEnter bid: \n");
	char bid[1000];
	fgets(line, sizeof(line), stdin);
	int fd = open(fname, O_CREAT|O_APPEND|O_RDWR);

	// find out if this new bid is higher than the old bid
	
	
	write(fd, line, strlen(line));
	close(fd);
	//printf("This is entered bid: %s\n", line);
	
	return 0;
}
