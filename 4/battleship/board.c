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
int  *fp;
  
printf("\nNew command name: %s\n" , name);
  // scanf("%s", &name);

  fp = open("a.txt", O_WRONLY | O_APPEND);
  write(fp, name, 256);
  close(fp);
  

 
}

int canCommand(char * name ){//return non zero of successful and prints contents of the file
  // that stores all the commands
  char *file_contents;
  long input_file_size;
  FILE *input_file = fopen("a.txt", "rb");
  fseek(input_file, 0, SEEK_END);
  input_file_size = ftell(input_file);
  rewind(input_file);
  file_contents = malloc(input_file_size * (sizeof(char)));
  fread(file_contents, sizeof(char), input_file_size, input_file);
  fclose(input_file);
  //sets last char to zero
  
  file_contents = malloc((input_file_size + 1) * (sizeof(char)));
  fread(file_contents, sizeof(char), input_file_size, input_file);
  fclose(input_file);
  file_contents[input_file_size] = 0;
  return strstr(file_contents, name);
}

void printAll() { //works fine
int character;
FILE * filepointer = fopen("grid.txt",  "r" ) ;
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
 printf("\n\n\n");
 char* p="that";
 printf("%d ", canCommand(p));
}
