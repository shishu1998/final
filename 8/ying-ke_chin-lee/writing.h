#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

char *bidfile = "curr_bid.txt";
char *bidderfile = "bidders.txt";
int fd;
int success_write = 1;


char entered_bid[256];

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

/* adapted from le K&R */
void reverse(char s[]) {
	int length = strlen(s);
	int c, i, j;
	for (i = 0, j = length-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	} 
	s[length-1] = '\0'; //get rid of the awful junk at end now
}

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

char *del_newline(char *in) {
	char *c;
	if ((c=strchr(in, '\n')) != NULL)
		*c = '\0';
	return in;
}

int file_write(char *to_write, char *pno) {
	int shmkey = ftok("control.c", 'a');
	int semkey = ftok("control.c", 'b');
//	printf("semkey = %d, shmkey = %d\n", semkey, shmkey);

	int semid = semget(semkey, 1, IPC_CREAT|0644);

	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	sb.sem_op = -1;
	semop(semid, &sb, 1);

	int shid = shmget(shmkey, sizeof(int), 0644);
//	printf("shid = %d\n", shid);

	char* shmem = shmat(shid, 0, 0); 
	FILE *fp, *fp_bidder;

	/* CHECK WHAT WAS THE LAST BID */
	fp = fopen(bidfile, "r");
	fseek(fp, 0, SEEK_END);
	char last_bid[256]; //hopefully enough space
	char new_char;
	int index = 0;
	new_char = fgetc(fp);
	while (new_char != '\n') {
		last_bid[index] = new_char;
		index++;

		fseek(fp, -1*index, SEEK_END);
		new_char = fgetc(fp);
	}
	fclose(fp);
	last_bid[index] = '\0';
	
	/* FLIP THE STRING AAAAACK *flips table* */
	reverse(last_bid);
	printf("last_bid is %s\n", last_bid);

	/*
		WRITE IN THE NEW BID IF POSSIBLE
	*/

	if (atoi(last_bid) >= atoi(to_write)) {
		printf("bid unsuccessful...\n");
		success_write = 0;
		return 0;
	}

	fp = fopen(bidfile, "a");
	printf("Error %d: %s\n", errno, strerror(errno));
	// open bidderfile

	fp_bidder = fopen(bidderfile, "a");
	printf("Error %d: %s\n", errno, strerror(errno));
	fprintf(fp_bidder, "%s\n", pno);
	fclose(fp_bidder);

	char line[256];
	strcpy(line, to_write); //this might be necessary...

	// find out if this new bid is higher than the old bid
	printf("This is entered bid: %s\n", line);

	*shmem = strlen(line);

	char *line_del_newline = del_newline(line);

	char *str = del_newline(to_write);
	int check1 = fprintf(fp, "\n");
	int check = fprintf(fp, "%s", str);
	if ((check1 < 0) || (check < 0)) printf("error fprint-ing\n");

	fclose(fp);
	close(fd);
	printf("Bid successful\n");

	shmdt(shmem);
	sb.sem_op = 1;
	semop(semid, &sb, 1);

	printf("completed write\n"); 
	return 0;
}
