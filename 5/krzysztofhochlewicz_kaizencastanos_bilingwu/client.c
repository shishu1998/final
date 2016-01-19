#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
//char curr;

char completed_words[1024] = "";
char *current_word;
char current_typed[128];
char current_char;
int entered_chars;
char remaining_words[] = "This is a sample sentence for you to type as you are typing.";
char *rwp = remaining_words; //frustrating C string stuff that is necessary for some reason
const char *delim = " ";
char current_status[1024];

void update_screen();

//main function driving the game
int main(){
	printf("%s\n", game_header);
	printf("\n");
	printf("%s\n", remaining_words);
	//printf(KWHT "test\n");
	//while(1){
	//	curr = get_letter();
	//	printf("\033[2J\033[1;1H");
	//	printf("\nGot %c\n", curr);
	//}
	
	current_word = strsep(&rwp, delim); //get the first word
	//strcat(current_word, " ");
	//printf("%s\n", rwp);
	while(current_word != NULL){ 				 //loop over words until there are no more words
		entered_chars = 0;
		current_typed[0] = 0;
		while(strcmp(current_word, current_typed)){ //loop until the user enters the current word correctly
			current_char = get_letter(); //wait for a key to be pressed
			if (current_char ==  127){   //if backspace pressed
				if (entered_chars > 0){  //if there are entered chars for the current word
					entered_chars--;
					current_typed[strlen(current_typed)-1] = 0; //get rid of last letter
				}
				//printf("got backspace\n");
			}
			else{ //if not a backspace
				entered_chars++;
				current_typed[strlen(current_typed)+1] = 0;
				current_typed[strlen(current_typed)] = current_char;
				//strcat(current_typed, current_char);	
			}
			printf("\033[2J\033[1;1H"); //clear the screen
			update_screen(); //update status
		}
		strcat(completed_words, current_word);
		strcat(completed_words, " ");
		current_word = strsep(&rwp, delim);
		
		//strcat(current_word, " ");
	}

	
	return 0;
}

void update_screen(){
	printf("%s\n", game_header);
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
	
}
