#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

//char *fname = "bids.txt"; // will have to make one bid file per item later on
char *bidfile = "curr_bid.txt";
int fd;

char entered_bid[256];

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

/* courtesy of le K&R */
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
	printf("w:getchar hang?\n");
    } while (c != '\n' && c != EOF);
	printf("w:out of getchar\n");
}

char *del_newline(char *in) {
	char *c;
	if ((c=strchr(in, '\n')) != NULL)
		*c = '\0';
	return in;
}

int file_write(char *to_write) {
	int shmkey = ftok("control.c", 'a');
	int semkey = ftok("control.c", 'b');
	printf("semkey = %d, shmkey = %d\n", semkey, shmkey);

	int semid = semget(semkey, 1, IPC_CREAT|0644);

	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	sb.sem_op = -1;
	semop(semid, &sb, 1);

	int shid = shmget(shmkey, sizeof(int), 0644);//IPC_CREAT|0644); 
	printf("shid = %d\n", shid);

	char* shmem = shmat(shid, 0, 0); // took out of below commented section
	FILE *fp;

	/* CHECK WHAT WAS THE LAST BID */
	fp = fopen(bidfile, "r");
	fseek(fp, 0, SEEK_END);
	char last_bid[256]; //hopefully enough space
	char new_char;
	int index = 0;
	int check_read = 0;
	new_char = fgetc(fp);
	printf("check_read = %d\n", check_read);
	printf("does fp work? %c\n", fp);
	while (new_char != '\n') {
		printf("I am inside the loop\n");
		last_bid[index] = new_char;
		index++;

		fseek(fp, -1*index, SEEK_END);
		new_char = fgetc(fp);
	}
	fclose(fp);
	last_bid[index] = '\0';
	printf("last_bid (backwards) is %s\n", last_bid);
	
	/* FLIP THE STRING AAAAACK *flips table* */
	reverse(last_bid);
	printf("last_bid (forwards?) is %s\n", last_bid);

	/*
		WRITE IN THE NEW BID IF POSSIBLE
	*/

	if (atoi(last_bid) >= atoi(to_write)) {
		printf("bid unsuccessful...\n");
		return;
	}

	fp = fopen(bidfile, "a");

	char line[256];
	strcpy(line, to_write); //this might be necessary...

	// find out if this new bid is higher than the old bid
//	printf("previous bid = %s\n", prev_bid);
	printf("This is entered bid: %s\n", line);

	*shmem = strlen(line);

//	char *prev_del_newline = del_newline(prev_bid);
	char *line_del_newline = del_newline(line);

//	printf("p_d_n = %s, l_d_n = %s\n", prev_del_newline, line_del_newline);
	printf("strlen = %zu, to_write = %s\n", strlen(to_write), to_write);
	char *str = del_newline(to_write);
	int check1 = fprintf(fp, "\n");
	int check = fprintf(fp, "%s", str);//to_write);
	printf("is check negative? %d\n", check);

	fclose(fp);
	close(fd);
	printf("Bid successful\n");

	shmdt(shmem);
	sb.sem_op = 1;
	semop(semid, &sb, 1);

	printf("completed write\n"); //ah, so it never gets here....why is that?  
	return 0;
}
