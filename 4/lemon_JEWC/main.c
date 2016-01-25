#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <sys/time.h>

/*kbhit implementation taken from http://http://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
 */

void changemode(int dir)
{
  static struct termios oldt, newt;
 
  if ( dir == 1 )
  {
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  }
  else
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}
 
int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;
 
  tv.tv_sec = 0;
  tv.tv_usec = 0;
 
  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);
 
  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);
 
}


/*Modified from 
http://www.sanfoundry.com/c-program-insert-word-desired-location/
*/
void editstring()
{
    int i, j, count = 0, pos, flag = 0;
    char s1[100], s2[10], s3[100];
    char *ptr1, *ptr2, *ptr3;
 
    printf("\nenter the String:");
    scanf(" %[^\n]s", s1);
    printf("\nenter the string to be inserted:");
    scanf(" %[^\n]s", s2);
    printf("\nenter the position you like to insert:");
    scanf("%d", &pos);
 
    ptr1 = s1;
    ptr3 = s3;
    /*COPYING THE GIVEN STRING TO NEW ARRAY AND INSERTING THE STRING IN NEW ARRAY*/
    for (i = 0, j = 0;*ptr1 != '\0'; ptr1++, i++, j++, ptr3++)
    {
        s3[j] = s1[i];
        if (*ptr1 == ' ' && flag != 1)
            ++count;
        if (flag != 1 && count == pos - 1)
        {
            flag = 1;
            for(ptr2 = s2;*ptr2 != '\0'; ptr2++)
            {
                s3[++j] = *ptr2;
                ptr3++;
            }
            s3[++j] = ' ';
            ptr3++;
        }
    }
    s3[j] = '\0';
    printf("\nthe string after modification is\n\n %s\n", s3);
}

int main(){
  int file;
  printf("\e[7mPlease enter the name of the file you are creating or editing.\e[27m\n");
  char response[100];
  fgets(response,100,stdin);
  strtok(response,"\n");
  if(access(response,F_OK)!=-1){
    printf("\e[7m%s\e[27m exists. Now opening.\n\n",response);

    int pid1 = fork();
    if(!pid1){ 
    execlp("cat","cat",response,NULL);
    }
  }
  else{
    printf("\e[7m%s\e[27m does not exist. Now creating.\n",response);
    file=open(response, O_CREAT, 0644);
    close(file);
  }
  //Opening file
  file=open(response, O_RDWR, 0644);
  
  int ch;
  while(1){
    changemode(1);
    while(!kbhit()){
      //print whole file
      int i = 0;
    }
    ch = getchar();
    printf("Entered %c\n",ch);
    changemode(0);
  }
  
  //closing file
  close(file);
  
  return 0;
}
 
