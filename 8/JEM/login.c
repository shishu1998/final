#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define USER_LEN 20 //length of username
#define PSWD_LEN 20 //length of password
#define BUFFER_LEN 500 //# of characters read from username.txt 

void make_profile(char *username, char *password) {

}

void find_user() {
  FILE* fd1 = fopen("username.txt", "r");//open username.txt
  char user[USER_LEN]; char pswd[PSWD_LEN];
  char underscore[3] = "_\0";
  char *username;
  //retrieves username and password
  printf("Please type in your username:\n");
  fgets(user, USER_LEN, stdin);
  printf("Please type in your password:\n");
  fgets(pswd, PSWD_LEN, stdin);
  printf("user: %s\n", user);
  printf("pswd: %s\n", pswd);  

  username = calloc(strlen(user) + strlen(pswd) + 1 + 1, sizeof(char));//1 is for the underscore and the other is for the null char               
  strcat(username, user);                                                                                                                         
  char *line = (char *)calloc(strlen(user) + strlen(pswd) + strlen(underscore) + 1, sizeof(char));                                                                 
  line = strsep(&username, "\n");                                                                                                                 
  strcat(line, underscore);
  strcat(line, pswd);                                                                                                                             
  printf("line: %s\n", line); 
  
  char *buffer = (char *)malloc(BUFFER_LEN*sizeof(char));
  fread(buffer, sizeof(char), BUFFER_LEN, fd1);
  //printf("strlen(buffer) = %lu\n", strlen(buffer));
  printf("buffer: %s\n", buffer);
  if (strstr(buffer, line) == NULL)
    printf("find_user() returned NULL. You typed incorrectly.\n");
  else
    printf("HUZZAH. You are a valid user! \n");
  buffer = "";
  printf("buffer after fread/fwrite: %s\n", buffer);
  
}

int main() {
  char user[USER_LEN]; char pswd[PSWD_LEN];
  char underscore[1] = "_";
  char *username;
  char yes_no;
  printf("=======WELCOME TO MARY'S PROM DATE SERVER=======\nYou want to take Mary out to PROM because she is an awesome person and if you don't want to then you have bad taste in women.\n\nPlease type in 1 if you have an account or 2 if you'd like to make one.\n");
  fgets(&yes_no, 3, stdin);
  printf("yes_no value:%c\n", yes_no);
  
  if (yes_no == '1') {
    find_user(); 
    /*FILE* fd1 = fopen("username.txt", "r");
    printf("Please type in your username:\n");
    fgets(user, USER_LEN, stdin);
    printf("Please type in your password:\n");
    fgets(pswd, PSWD_LEN, stdin);
    char *buffer = (char *)malloc(100*sizeof(char));
    //printf("sizeof(buffer) = %lu\n", sizeof(buffer));
    fread(buffer, sizeof(char), 100, fd1);
    printf("buffer: %s\n", buffer);
    buffer = "";
    printf("buffer after fread/fwrite: %s\n", buffer);    
    */
  }
  else if (yes_no == '2'){
    FILE* fd1 = fopen("username.txt", "a+");
    printf("Please create a username:\n");
    fgets(user, USER_LEN, stdin);
    printf("Please create a password:\n");
    fgets(pswd, PSWD_LEN, stdin);
    //printf("username array: %s\n", user);
    //printf("pswd array: %s\n", pswd);
    username = calloc(strlen(user) + strlen(pswd) + 1 + 1, sizeof(char));//1 is for the underscore and the other is for the null char
    //password = calloc(strlen(pswd) + 1, sizeof(char));
    strcat(username, user);
    char *line = (char *)calloc(strlen(user) + strlen(pswd) + 1 + 1, sizeof(char));
    line = strsep(&username, "\n");
    //printf("sizeof(username) = %lu\n", strlen(username));
    strcat(line, underscore);
    //printf("username: %s\n", username);
    //strcat(password, pswd);
    strcat(line, pswd);
    printf("line: %s\n", line);
    
    fwrite(line, sizeof(char), strlen(line), fd1);
       
    fclose(fd1);
    return 0;
  }
  else
    printf("STOP SABOTAGING THIS PROGRAM AND GIVE US EITHER 1 OR 2 AS YOUR ANSWER. SMH PEOPLE THESE DAYS\n");
}
