//this is meant to be the file that writse a history of one's commands to a file
//will have to read the file to see if a shot fired actually hits
//creates a randomly generated board, and can print and manipulate it according to a command <whatevs the user inputed>
//feel free to test, once a working connection is made this is basically done
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



/* int storeCommand(char * name) {//keeps a log of all entered commands , whether a correct input of not */
/*   //needed so that a command isnt entered twice */
/*   char * entry; */
/* int  *fp; */
  
/* printf("\nNew command name: %s\n" , name); */
/*   // scanf("%s", &name); */

/*   fp = open("a.txt", O_WRONLY | O_APPEND); */
/*   write(fp, name, 256); */
/*   close(fp); */
  

 
/* } */
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

  // printf("%s" , buffer);
  //returns a non zero if true. this means that the command can be carried on
  // return strstr(buffer, name);
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
  //printf("%s" ,strerror(errno));
}


//this is in the format of 1A,1B,1C,1D...4D and will be printed out 
//in prettier form in another function
//they will, however, be represented by digitsn in this simplified array
//0 means ship not shot
//1 means ship that is shot 
//-1 means no ship there to begin with
//makes it easy to randomly generate the nums
void newPrint(int  a[]){//prints out a pretty board with the info given
  printf("\n\n	A	B	C	D\n-------------------------------------\n 1     |  %d   |  %d  |  %d  |  %d    \n -------------------------------------\n 2     |  %d   |  %d  |  %d  |  %d    \n -------------------------------------\n 3     |  %d   |  %d  |  %d  |  %d    \n -------------------------------------\n4     |  %d   |  %d  |  %d  |  %d    \n", a[0],a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15]);
 }




int numGenerator(){//gives either -1 or 0 by reading from the rand file. This will be used to randomly generate boards
  //WORKING
  //int x = rand();  WRONG
  int num;
  int x = open("/dev/random",O_RDONLY);
  read(x, &num, 4);//4 because 4 bytes
  close(x);
  //printf("number read from dev file is %d\n",num);
  if (num>=0){//MAX_RAND is 2147483647 min is -2147483648
    return -1;}
  else
    return 0;


}
int realBoard[16]; //represents the real board
void boardGenerator(){//uses numGenerator to create the array that represents the board
  // return NULL;
  int n = 0;
  while (n <16) {
    realBoard[n] = numGenerator();
  n = n + 1;
  }
}


void editBoard(char * command) {//assumes command has no  '\n' on it. edits the array of -1 and zeroes according to inputs
  //commands should be  '1A, 3B , etc ' 
  //in changing realBoard, it changes the board of the user, and therefore whats printed in newPrint(int a[])
  if (strcmp(command, "1A") == 0){
    if (realBoard[0]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[0] =  1;
    }
  }
  else if (strcmp(command, "1B") == 0){
    if (realBoard[1]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[1] =  1;
    }
  }
  else if (strcmp(command, "1C") == 0){
    if (realBoard[2]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[2] = 1;
    }
  }
  else if (strcmp(command, "1D") == 0){
    if (realBoard[3]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[3] = 1;
    }
  }
  else if (strcmp(command, "2A") == 0){
    if (realBoard[4]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[4] = 1;
    }
  }
  else if (strcmp(command, "2B") == 0){
    if (realBoard[5]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[5] = 1;
    }
  }
  else if (strcmp(command, "2C") == 0){
    if (realBoard[6]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[6] = 1;
    }
  }
  else if (strcmp(command, "2D") == 0){
    if (realBoard[7]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[7] = 1;
    }
  }
  else if (strcmp(command, "3A") == 0){
    if (realBoard[8]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[8] =  1;
    }
  }
  else if (strcmp(command, "3B") == 0){
    if (realBoard[9]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[9] =  1;
    }
  }
  else if (strcmp(command, "3C") == 0){
    if (realBoard[10]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[10] = 1;
    }
  }
  else if (strcmp(command, "3D") == 0){
    if (realBoard[11]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[11] = 1;
    }
  }
  else if (strcmp(command, "4A") == 0){
    if (realBoard[12]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[12] =  1;
    }
  }
  else if (strcmp(command, "4B") == 0){
    if (realBoard[13]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[13] = 1;
    }
  }
  else if (strcmp(command, "4C") == 0){
    if (realBoard[14]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[14] =  1;
    }
  }
  else if (strcmp(command, "4D") == 0){
    if (realBoard[15]==-1){
      printf("\n\n its a miss bro\n");
    }
    else{
      realBoard[15] = 1;
    }
  }
  
  
}
int main() {
  //testin to see if it writes
  //int x = storeCommand("A1") ; 
//printf( "\n %d " , x);
//printAll();
  //printf("\n\n\n");
  ///char* p="melee"; //if this is melee return 0
  //printf("%d ", canCommand(p));
  printf("\n\n\n");
 // writer(p);
 //int realboard[16] = { 0 , -1,0,0,-1 ,-1 ,-1 ,0,0,0,0,-1,0,-1,0,-1};//for testing purposes

 //newPrint(realboard);
 // printf("max random number is %d\n", RAND_MAX);
  // printf("random num is : %d  \n" , numGenerator() );//should print 0 or -1 with equal chance
  //printf("anotha random num is : %d  \n" , numGenerator() );
  // printf("anotha random num is : %d  \n" , numGenerator() );
  //printf("\nbefore randomization"); 
  //newPrint(realBoard);
  //boardGenerator() ;
  //printf("\n after board randomization"); 

  // newPrint(realBoard);
  //ALL WORKING AT THIS POINT
  char * c = "1A";
  realBoard[0] = -1;
  editBoard(c);
  printf("%d\n" , realBoard[0]);
  newPrint(realBoard);
 

  //NOW EVERY FUNCTION WORKS IN THIS FILE, ONTO THE BIG BOY STUFF
 return 0;
}
