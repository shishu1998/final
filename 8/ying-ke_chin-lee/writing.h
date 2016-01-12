#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

//extern Lot *pcurr_lot;
Lot *pcurr_lot;

char *fname = "bids.txt"; // will have to make one bid file per item later on

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

int main_w() {
	int shmkey = ftok("control.c", 'a');
	int semkey = ftok("control.c", 'b');
	printf("semkey = %d, shmkey = %d\n", semkey, shmkey);

	int semid = semget(semkey, 1, IPC_CREAT|0644);

	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	sb.sem_op = -1;
	semop(semid, &sb, 1);

	int shid = shmget(shmkey, sizeof(int), 0644);
	printf("shid = %d\n", shid);

	int fd = open(fname, O_RDONLY);
	int* shnum = shmat(shid, 0, 0);

	lseek(fd, -1 * (*shnum), SEEK_END);

	char prev_bid[*shnum];
	read(fd, &prev_bid, *shnum);
	close(fd);

	fd = open(fname, O_WRONLY|O_APPEND);
	printf("\nEnter bid: \n");
	char line[256];
	getchar();
	fgets(line, sizeof(line), stdin);
	printf("fgets received %s\n", line);

	// find out if this new bid is higher than the old bid
	printf("previous bid = %s\n", prev_bid);
	printf("This is entered bid: %s\n", line);
	
	printf("tried to print1\n");
	print(*pcurr_lot);
	printf("tried to print2\n");

	*shnum = strlen(line);
	char *tmp = line;

	if (atof(prev_bid) >= atof(line)) {
		printf("You cannot bid that amount.\n");
	} else {
		write(fd, tmp, *shnum);
		printf("Bid successful\n");
	}
	
	close(fd);
	shmdt(shnum);
	sb.sem_op = 1;
	semop(semid, &sb, 1);

	return 0;
}
