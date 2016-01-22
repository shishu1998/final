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
//works now
//serves as the boolean that prevents moved from repeating
int canCommand(char * name ){//return non zero if successful and prints contents of the file
  // that stores all the commands
  
  char * buffer = 0;
  long length;
  FILE * f = fopen ("a.txt", "rb");
  
  if (f)
    {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);
      buffer = malloc (length);
      if (buffer)
	{
	  fread (buffer, 1, length, f);
	}
      fclose (f);
    }

  printf("%s" , buffer);
  //returns a non zero if true. this means that the command can be carried on
  return strstr(buffer, name);
}
//prints the current board
void printAll() { //works fine
int character;
FILE * filepointer = fopen("grid.txt",  "r" ) ;
//while char not at end of file
while ((character=fgetc(filepointer)) != EOF) {
putchar(character); /* print the character */
 }
}
//writes inputed commands to a file
//serves as a  sort of "history keeper"
 void writer(char * command) {
   int fp;
   
 fp = open("a.txt", O_WRONLY | O_APPEND);
 write(fp, command, sizeof(command));
  close(fp);
  printf("%s" ,strerror(errno));
}

int realboard[12] = { 0 , -1,0,0,-1 ,-1 ,-1 ,0,0,0,0,-1};//for testing purposes
//this is in the format of 1A,1B,1C,1D...4D and will be printed out 
//in prettier form in another function
//they will, however, be represented by digitsn in this simplified array
//0 means ship not shot
//1 means ship that is shot 
//-1 means no ship there to begin with
//makes it easy to randomly generate the nums
void newPrint(){//still not finished yet
   printf("\n\n	A	B	C\
	D\n-------------------------------------\n\
1     |  %d   |  %d  |  %d  |  %d    \n \
-------------------------------------\n\"", 0);
 }




int main() {
  //testin to see if it writes
  //int x = storeCommand("A1") ; 
//printf( "\n %d " , x);
//printAll();
 printf("\n\n\n");
 char* p="baloney";
 printf("%d ", canCommand(p));
 printf("\n\n\n");
 writer(p);
 newPrint();
}
