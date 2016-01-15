//this is meant to be the file that writse a history of one's commands to a file
//will have to read the file to see if a shot fired actually hits


#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int storeCommand(char * name) {//keeps a log of all entered commands , whether a correct input of not
  //needed so that a command isnt entered twice
  char * entry;
FILE  *fp;
  
printf("\nNew command name: %s\n" , name);
  // scanf("%s", &name);

  fp = open("a.txt", O_WRONLY | O_APPEND);
  write(fp, name, 256);
  close(fp);
  

 
}
null printAll() { 
int character;
FILE * filepointer = fopen("a.txt",  "r" ) ;
//while char not at end of file
while ((character=fgetc(filepointer)) != EOF) {
putchar(character); /* print the character */
}
}
int main() {
  //testin to see if it writes
  //int x = storeCommand("A1") ; 
//printf( "\n %d " , x);
printAll();
}
