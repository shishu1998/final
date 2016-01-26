//SERVER-PLAYER1
//SERVER
//SERVER
#include <stdio.h>
#include <stdlib.h>

#include <string.h> 
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "key_listener.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

char game_header[] = "************************* Welcome to bootleg TypeRacer! ************************";
char sample_text[] = "This is a sample sentence.\n";

char completed_words[1024] = "";
int number_of_words;
char *current_word;
char current_typed[128];
char current_char;
int entered_chars;
char remaining_words[] = "This is a sample sentence for you to type as you are typing. ";
char *rwp = remaining_words; //frustrating C string stuff that is necessary for some reason
const char *delim = " ";
char current_status[1024];

int socket_id, socket_client,pid;
char buffer[256];

void update_screen();
char* makeData();
int getData(char* str);


int main(){
  
  //--------------------//
  //----Network Stuff----//
  //--------------------//
  
  //create the socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);
  	      //AF_INET is the Ip address in IPv4, SOCK_STREAM is the stream of data packets going in, 0 is the default (lets your OS take care of stuff) 
  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET; //socket type IPv4
  listener.sin_port = htons(5000); //port #, htons(#) is a numberic conversion function. it is necessary because of the way a computer stores integers. the htons will take the way your computers way of handling bit order of storing integers and turn it into something that a NETWORK can use.
  listener.sin_addr.s_addr=INADDR_ANY; // bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  listen(socket_id,1);//opens the socket up for a connection
  printf("<server> listening\n");
  
  socket_client = accept(socket_id, NULL, NULL);
  printf("<server> connected: %d\n", socket_client);
  
  //write(socket_client, "stuff", 6);
  printf("Get Ready! Game Starting Soon!\n");
  sleep(4);
  printf("Game starting in three--\n");
  sleep(1);
  printf("two--\n");
  sleep(1);
  printf("one--\n");
  sleep(1);
  
  //---------------------------//
  //----The Actual Game Bit----//
  //---------------------------//
  clock_t start = clock(), diff;
  printf("\033[2J\033[1;1H"); //clear the screen
  printf("%s\n", game_header);
  printf("\n");
  printf("%s\n", remaining_words);
	
  current_word = strsep(&rwp, delim); //get the first word

  int check_1 = 0; //Used to fix a bug where a space kept appearing after you typed a word
  int check_2 = 1; //To keep the first check from affecting the first word
  while(current_word != NULL){
    //loop over words until there are no more words
    entered_chars = 0;
    current_typed[0] = 0;
    if(check_2 != 1)
      check_1 = 1;
			
    while(strcmp(current_word, current_typed)){ //loop until the user enters the current word correctly
      current_char = get_letter(); //wait for a key to be pressed
      if (current_char ==  127){   //if backspace pressed
	if (entered_chars > 0){  //if there are entered chars for the current word
	  entered_chars--;
	  current_typed[strlen(current_typed)-1] = 0; //get rid of last letter
	}
      }
      else{ //if not a backspace
	entered_chars++;
	current_typed[strlen(current_typed)+1] = 0;
	current_typed[strlen(current_typed)] = current_char;
      }
      printf("\033[2J\033[1;1H"); //clear the screen
      update_screen(); //update status
			
      if(check_1)
	current_typed[0] = 0;
      check_1 = 0;
    }
		
    strcat(completed_words, current_word);
    strcat(completed_words, " ");
    current_word = strsep(&rwp, delim);
    check_2 = 0;
    number_of_words++;
    
    //THUS BEGINS SENDING INFORMATION TO PLAYER2 (CLIENT)
    //MAY THE ODDS BE EVER IN MY FAVOR
    int converted_number = htonl(number_of_words);
      
      /*
      recv(socket_client, buffer, sizeof(buffer), 0);
      printf("<server> Recieved:[%s]\n", buffer);
      strtok(buffer, "\n");
      send(socket_client, number_of_words, sizeof(number_of_words), 0); //FOR INT STUFFS WE JUST HAVE TO GET THAT AS A VARIABLE AND FUCKING SEND THAT SHIT HERE
      */
    write(socket_client, &converted_number, sizeof(converted_number));
  
    int received_int = 0;
    int return_status;
    return_status = read(socket_client, &received_int, sizeof(received_int));
    if (return_status > 0) {
      fprintf(stdout, "Received int = %d\n", ntohl(received_int));
    }
    else {
      printf("<client>Failed to read");
    }
    
    //if ever the need to comment new stuff out, end it here
  }

  //Return the time
  diff = clock() - start;
  int msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("\nTime taken: %d seconds %d milliseconds\n", msec/1000, msec%1000); //Exact time
  printf("Words per minute: %f WPM\n", (13.0/(msec/1000))* 60); //words divided by seconds, multiplied by 60 seconds



  return 0;
}


int a = 0;
void update_screen(){
  /*write(socket_client, makeData(), 6);
    if(read(socket_client, buffer, sizeof(buffer)) !=-1){
    a = getData(buffer);
    }*/
  //--print statements--//
  printf("%s\n", game_header);
  printf("\n");
  printf("%i\n", a);
  printf("\n");
  strcpy(current_status, " ");
  strcat(current_status, KGRN);
  strcpy(current_status, completed_words);
  strcat(current_status, KGRN);
  strcat(current_status, current_word); 
  strcat(current_status, " "); 
  strcat(current_status, KWHT);
  strcat(current_status, rwp);
  printf("%s\n", current_status);
  printf("\n");
  printf("%s\n", current_typed);
  buffer[0] = 0;
}
char * makeData(){
  char* str;
  sprintf(str, "%d", number_of_words);
  return str;
}
int getData(char* str){
  char *eptr;
  long result;
  result = strtol(str, &eptr, 10);
  return (int) (long) result;
}
