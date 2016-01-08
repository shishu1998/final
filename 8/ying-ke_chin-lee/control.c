#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

/*
	"-r" CORRESPONDS TO RMV SHAREDMEM AND DISPL FILE
	"-c" CREATS SHAREDMEM, SETUP
*/

char *fname = "bids.txt";
int fd;
int semkey;
int semid;
int shmkey;
int shmid;

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

struct sembuf sb;

void print_story() {
	FILE *fp;
	fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("could not open\n");
		exit(1);
	}

	char line[1000];
	char *l;
	while ( fgets(line, sizeof line, fp)) {
		printf("%s", line);
	}
}

void create() {
	int fd;
	fd = open(fname, O_TRUNC);
	
	shmkey = ftok("control.c", 'a');
	if (shmkey < 0) printf("shmkey: error %d: %s\n", errno, strerror(errno));

	semkey = ftok("control.c", 'b');
	if (semkey < 0) printf("semkey: error %d: %s\n", errno, strerror(errno));

	shmid = shmget(shmkey, 1, IPC_CREAT|0666);
	if (shmid < 0) printf("shmid: error %d: %s\n", errno, strerror(errno));

	semid = semget(semkey, 1, IPC_CREAT|0666);
	if (semid < 0) printf("semid: error %d: %s\n", errno, strerror(errno));
	
	sb.sem_num = 0;
	sb.sem_op = -1;
	sb.sem_flg = SEM_UNDO;

//	printf("got here\n");
//	semop(semid, &sb, 1);
}

/* NOT IN USE YET
void remv() {
	close(fd);

	printf("closing: semkey = %d, semID = %d\n", semkey, semid);
	printf("closing: shmkey = %d, shmID = %d\n", shmkey, shmid);
	sb.sem_op = 1;
	semop(semid, &sb, 1);

	semctl(semid, 0, IPC_RMID);
	shmctl(shmid, IPC_RMID, NULL);

	printf("\nclosed: semkey = %d, semID = %d\n", semkey, semid);
	printf("closed: shmkey = %d, shmID = %d\n", shmkey, shmid);
	
	printf("\nFull story:\n");
	print_story();
}
*/

int main(int argc, char **argv) {
	if (argc == 1) {
		printf("You are missing an argument.\n");
		exit(1);
	}
	if (strcmp(argv[1], "-c") == 0) {
		create();
	} else if (strcmp(argv[1], "-r") == 0) {
		remv();
	} else {
		printf("You have entered an invalid argument.\n");
	}
	return 0;
}
