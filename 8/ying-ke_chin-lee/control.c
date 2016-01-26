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
	shmid = shmget(shmkey, sizeof(int), IPC_CREAT|0644);
	semid = semget(semkey, 1, IPC_CREAT|0644);

	fd = open(fname, O_APPEND);
	close(fd);
	
	semctl(semid, 0, SETVAL, 1);

}


void remv() {
	shmid = shmget(shmkey, sizeof(int), -644);
	semid = semget(semkey, 1, 0644);

	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID);

	fd = open(fname, O_RDONLY);
	struct stat sf;
	stat(fname, &sf);
	char fst[sf.st_size];
	read(fd, fst, sf.st_size);
	printf("%s\n", fst);

	close(fd);
}


int main(int argc, char **argv) {
	shmkey = ftok("control.c", 'a');
	if (shmkey < 0) printf("shmkey3: error %d: %s\n", errno, strerror(errno));

	semkey = ftok("control.c", 'b');
	if (semkey < 0) printf("semkey3: error %d: %s\n", errno, strerror(errno));

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
