#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

const char * tutorlogin() {
	int tutoraccounts = open("tutoraccounts.txt", O_RDWR | O_APPEND, 0644);
        if (tutoraccounts < 0) {
                printf("Error %d: %s\n", errno, strerror(errno));
        }

	//ask if they want to register or login
		//separate functions?

	printf("Please enter your login information.\n");

	printf("Username: ");
	char username[100];
	fgets(username, sizeof(username),stdin);

	//search for username in tutoraccounts.txt
	//if it exists, ask for password
	//if not, ask to create account and double check password
}

int main() {
	int tutoraccounts = open("tutoraccounts.txt", O_CREAT | O_TRUNC, 0644);
	if (tutoraccounts < 0) {
		printf("Error %d: %s\n", errno, strerror(errno));
	} else {
		printf("Program laoded.\n");
	}
	close(tutoraccounts);

	printf("\nHello and welcome to MovieFone--wait, sorry. Wrong program\n");
	printf("Hello and welcome to ARISTA chat!\n");

	int moveon = 0;
	while (moveon == 0) {
		printf("\nAre you a tutor or a tutee?\n");
		char student[100];
		fgets(student, sizeof(student), stdin);

		if (strcmp(student,"tutor") >= 0) {
			printf("\nWelcome tutor! Please login.\n");
			moveon = 1;
			int loggedin = 0;
			while (loggedin == 0)
				if (tutorlogin()) {
					printf("Thank you for logging in %s\n");
					loggedin = 1;
				} else {
					printf("There was an error while logging in.")
					printf("Please try again.\n");
				}
			}
		} else if (strcmp(student, "tutee") >= 0) {
			printf("\nWelcome tutee!\n");
			moveon =1;
		} else {
			printf("We didn't understand your response. Please try again.\n");
		}
	}
}
