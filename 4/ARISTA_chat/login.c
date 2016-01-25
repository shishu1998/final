#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define USERNAME_LEN 4
#define PASSWORD_LEN 15

int find_error(char* username, char* password) {
  printf("Looking for user\n");
  if (username == NULL || password || NULL) {
    printf("Please enter a username/password that isn't null\n");
    return 0;
  }
  strsep(&username,": ");
  strsep(&password,": ");
  printf("Your user name is: %s\n",username);
  if (username == NULL && password == NULL) {
    printf("Your username/password are set!\n");
    return 1;
  } else {
    printf("Please don't have any newline, white space, or colon characters\n");
    return 0;
  }
}

int does_user_exist(char* username) {
  FILE* fd = fopen("tutoraccounts.txt","r");
  char user[USERNAME_LEN];
  char pswd[PASSWORD_LEN];
  char* buf = (char*)malloc(500*sizeof(char));
  fread(buf,sizeof(char),500,fd);
  username = strsep(&username,"\n");
  printf("Your username is: %s\n",username);
  if(strstr(buf,username) == NULL) { //username doesn't exist
    printf("You don't already have an account with us. Continue registering!\n");
    buf = "";
    fclose(fd);
    return 1;
  } else {
    printf("There is already an account with that username. Please try again.\n");
    buf = "";
    fclose(fd);
    return 0;
  }
}

void registered_user() {
  FILE* fd = fopen("tutoraccounts.txt","r");
  char username[USERNAME_LEN];
  char password[PASSWORD_LEN];
  char delimeter[3] = ":\0";
  char *tutor;
  printf("Please type in your username: \n");
  fgets(username, USERNAME_LEN, stdin);
  printf("Please type in your password: \n");
  fgets(password, PASSWORD_LEN, stdin);
  if(find_error(username, password)) {
    tutor = calloc(strlen(username) + strlen(password) + 1 + 1, sizeof(char));
    strcat(username, tutor);
    char *line = (char*)calloc(strlen(tutor) + strlen(password) + strlen(delimeter) + 1, sizeof(char));
    line = strsep(&username,"\n");
    strcat(line,delimeter);
    strcat(line,password);
    char* buf = (char*)malloc(500*sizeof(char));
    fread(buf,sizeof(char),500,fd);
    if(strstr(buf,line) == NULL) {
      printf("Your account information was incorrect. Please try again.\n");
    } else {
      print("You are logged in!\n");
    }
    buf = "";
  } else if(!(find_error(username,password))) {
    printf("Error logging in\n");
  } else {
    printf("Error finding account\n");
  }
}

int main() {
  char *line1 = "this is bad\n";
  printf("testing strstr: %s\n", strstr(line1, "\n"));

  char user[USERNAME_LEN]; char pswd[PASSWORD_LEN];
  char underscore[1] = ":";
  char *username;
  char yes_no;
  printf("Please type in 1 if you have an account or 2 if you'd like to make one\n");
  fgets(&yes_no, 3, stdin);
  printf("yes_no value:%c\n", yes_no);
  
  if (yes_no == '1') {
    registered_user(); 
  }
  else if (yes_no == '2'){
    FILE* fd1 = fopen("tutoraccounts.txt", "a+");
    printf("Please create a username:\n");
    fgets(user, USERNAME_LEN, stdin);
    printf("Please create a password:\n");
    fgets(pswd, PASSWORD_LEN, stdin);
    printf("username array: %s\n", user);
    printf("pswd array: %s\n", pswd);
    username = calloc(strlen(user) + strlen(pswd) + 1 + 1, sizeof(char));//1 is for the underscore and the other is for the null char
    strcat(username, user);
    char *line = (char *)calloc(strlen(user) + strlen(pswd) + 1 + 1, sizeof(char));
    line = strsep(&username, "\n");
    //printf("sizeof(username) = %lu\n", strlen(username));
    strcat(line, underscore);
    //printf("username: %s\n", username);
    //strcat(password, pswd);
    strcat(line, pswd);
    printf("line: %s\n", line);
    if (does_user_exist(user) == 0) {
    fwrite(line, sizeof(char), strlen(line), fd1);
    }
    else if (does_user_exist(user) == 1)
      printf("Please try again\n");
    fclose(fd1);
  }
  
  else
    printf("STOP SABOTAGING THIS PROGRAM AND GIVE US EITHER 1 OR 2 AS YOUR ANSWER. SMH PEOPLE THESE DAYS\n");
  return 0;
}


/*
int newuser() {
  int moveon = 0;
  int username = 0000;
  char passwd[16];
  while (moveon == 0) {
    printf("Type in your 4-digit ID for the username.\n");
    scanf("%i",&username);

    if (username >= 1000 && username <= 9999) {
      char *in = passwd;
      struct termios  tty_orig;
      char c;
      tcgetattr( STDIN_FILENO, &tty_orig );
      struct termios  tty_work = tty_orig;
      puts("Please input password:");
      tty_work.c_lflag &= ~( ECHO | ICANON );  // | ISIG );
      tty_work.c_cc[ VMIN ]  = 1;
      tty_work.c_cc[ VTIME ] = 0;
      tcsetattr( STDIN_FILENO, TCSAFLUSH, &tty_work );

      while (1) {
	if (read(STDIN_FILENO, &c, sizeof c) > 0) {
	  if ('\n' == c) {
	    break;
	  }
	  *in++ = c;
	  write(STDOUT_FILENO, "*", 1);
	}
      }

      tcsetattr( STDIN_FILENO, TCSAFLUSH, &tty_orig );

      *in = '\0';
      fputc('\n', stdout);

      char check[16];
      char *checkin =  check;
      struct termios  tty_check;
      char d;
      tcgetattr( STDIN_FILENO, &tty_check );
      struct termios  tty_checking = tty_check;
      puts("Please retype password:");
      tty_checking.c_lflag &= ~( ECHO | ICANON );  // | ISIG );
      tty_checking.c_cc[ VMIN ]  = 1;
      tty_checking.c_cc[ VTIME ] = 0;
      tcsetattr( STDIN_FILENO, TCSAFLUSH, &tty_checking );

      while (1) {
	if (read(STDIN_FILENO, &d, sizeof(d)) > 0) {
	  if ('\n' == d) {
	    break;
	  }
	  *checkin++ = d;
	  write(STDOUT_FILENO, "*", 1);
	}
      }

      tcsetattr( STDIN_FILENO, TCSAFLUSH, &tty_check );

      *checkin = '\0';
      fputc('\n', stdout);

      if(strcmp(passwd,check) != 0) {
	printf("Error: Passwords don't match. Please try again.\n");
      } else {
	break;
	moveon == 1;
      }
    } else {
      printf("Error: Invalid username. Please input your 4-digit ID.\n");
    }
  }

  char newuser[1000];
  snprintf(newuser,sizeof(newuser), "%i: %s\n",username,passwd);
  int fd = open("tutoraccounts.txt",O_RDWR | O_APPEND,0644);
  write(fd, newuser, strlen(newuser));
  close(fd);

  return username;
}

int registereduser() {
	FILE* fd;
	int line_num = 1;
	int find_result = 0;
	int username = 0000;

	printf("Type in your 4-digit ID for the username.\n");
    	scanf("%i",&username);

	if((fd = fopen("tutoraccounts.txt", "r")) == NULL) {
		return(-1);
	}

	char buffer[256];

	while(fgets(buffer, sizeof(buffer), fd) != NULL) {
		printf("%s\n",buffer);

		if((strstr(buffer, username)) != NULL) {
			printf("A match found on line: %d\n", line_num);
			printf("\n%s\n", buffer);
			find_result++;
		}

	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}

	//Close the file if still open.
	if(fd) {
		fclose(fd);
	}

  return 1;

}

int tutorlogin() {
  int tutoraccounts = open("tutoraccounts.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
  if (tutoraccounts < 0) {
    printf("Error %d: %s\n", errno, strerror(errno));
  }

  int accessing = 0;
  int username = 0;
  while (accessing == 0) {
    printf("Press 1 to login or 2 to register.\n");
    int action;
    scanf("%i",&action);
    if (action == 1) {
      username = registereduser();
      accessing = 1;
    } else if (action == 2) {
      username = newuser();
      accessing = 1;
    } else {
      printf("We didn't understand your response. Please try again.\n");
    }
  }

  //search for username in tutoraccounts.txt
  //if it exists, ask for password
  //if not, ask to create account and double check password

  printf("%i\n",username);
  return username;
}

int clean_stdin() {
	while (getchar() != '\n');
		return 1;
}

int main() {
  int tutoraccounts = open("tutoraccounts.txt", O_CREAT | O_TRUNC, 0644);
  if (tutoraccounts < 0) {
    printf("Error %d: %s\n", errno, strerror(errno));
  } else {
    printf("Program loaded.\n");
  }
  close(tutoraccounts);

  printf("\nHello and welcome to MovieFone--wait, sorry. Wrong program\n");
  printf("Hello and welcome to ARISTA chat!\n");

  int moveon = 0;
  char student;
  int rows;
  while (moveon == 0) {
	//((scanf("%d%c",&rows,&student)!=2 || student!='\n') && clean_stdin()) || rows==1 || rows==2) {
    printf("\nType 1 if you are a tutor or 2 if you are a tutee.\n");
    int student;
    char str[100];
    scanf("%[^1-2]%d",str,&student);
  //  while (((scanf("%d%c",&rows,&student)!=2 || student!='\n') && clean_stdin()) || rows==1 || rows==2) {
    if (student == 1) {
      printf("\nWelcome tutor! Please login.\n");
      int loggedin = 0;
      while (loggedin == 0)
	if (tutorlogin() != 0) {
	  printf("Thank you for logging in\n");
	  moveon = 1;
	  loggedin = 1;
	} else {
	  printf("There was an error while logging in.");
	  printf("Please try again.\n");
	}
    } else if (student == 2) {
      printf("\nWelcome tutee!\n");
      moveon =1;
    } else {
      printf("We didn't understand your response. Please try again.\n");
    }

  }
}
*/
