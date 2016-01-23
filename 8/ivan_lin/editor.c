#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>

#define CURSOR_UP "\033[1A"
#define CURSOR_DOWN "\033[1B"
#define CURSOR_RIGHT "\033[1C"
#define CURSOR_LEFT "\033[1D"
#define ALT_BUFFER "\033[?1049h\033[H"
#define PRESERVED_SCREEN "\033[?1049l"

typedef struct line {int term_line; 
  int file_line; 
  char* text; 
  char* status;
  struct line* next;} line;
typedef struct termios termios;
typedef struct winsize winsize;

int init(line*, winsize*);
int cleanup(line*);
int fill_buffers(int, int, line*);
int print_buffers(line*, winsize*);
int open_screen_buffer(termios*);
int open_preserved_screen(termios*);
int detect_keypress(int*, int*);
int get_cursor(int*, int*);//int*, int*);

int main(){
  int cursor_row, cursor_col, read_line;
  struct termios term;
  struct winsize window;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

  line* first_line = (line*)malloc(sizeof(line));
  line* changed_lines;

  init(first_line, &window);

  int map = open("./map",O_RDWR);

  fill_buffers(map,0,first_line);
 
  open_screen_buffer(&term);
  
  print_buffers(first_line,&window);

  while (detect_keypress(&cursor_row,&cursor_col)){
    //fflush(stdout);
  }
  
  open_preserved_screen(&term);

  cleanup(first_line);
  close(map);
}

int get_cursor(int* row, int* col){
  printf("\033[6n");
  int temp;
  temp = getchar();//\033
  temp = getchar();//]
  *row = getchar()-'0';//row
  temp = getchar()-'0';
  while (temp >= 0 && temp <= 9){
    *row = 10 * *row + temp; 
    temp = getchar()-'0';
  }
  //; divider
  *col = getchar()-'0';//col
  temp = getchar()-'0';
  while (temp >= 0 && temp <= 9){
    *col = 10 * *col + temp; 
    temp = getchar()-'0';
  }
  while (temp != 'R'-'0'){
    temp = getchar()-'0';
  }
}

int detect_keypress(int* cursor_row, int* cursor_col){
  int key;
  key = getchar();
  if (key == '\033'){
    if (getchar() == '['){
      key = getchar();
      if (key == 65){
	printf(CURSOR_UP);
	get_cursor(cursor_row, cursor_col);
      }
      else if (key == 66){
	printf(CURSOR_DOWN);
	get_cursor(cursor_row, cursor_col);
      }
      else if (key == 67){
	printf(CURSOR_RIGHT);
      }
      else if (key == 68){
	printf(CURSOR_LEFT);
      }
    }
  }
  else if (key == 17){//ctrl+q
    return 0;
  }
  else if (key == 127){
    printf(CURSOR_LEFT);
    printf("%c",' ');
    printf(CURSOR_LEFT);
  }
  else{
    printf("%c",key);
  }
}

int fill_buffers(int file, int start_read, line* first_line){
  FILE* fstream = fdopen(file,"r");
  size_t buff_size = sizeof((*first_line).text); 
  int read = (int)getline(&(*first_line).text, &buff_size, fstream);
  int i;
  while(first_line->next != NULL){
    read = (int)getline(&(*first_line).text, &buff_size, fstream);
    first_line = first_line->next;
  }
}
  
int print_buffers(line* first_line, winsize* window){
  while (first_line->next){
    printf("%*s\r%s",window->ws_col,first_line->status,first_line->text);
    first_line = first_line->next;
  }
}

int open_screen_buffer(termios* term){
  printf(ALT_BUFFER);
  tcgetattr(STDIN_FILENO,term);
  term->c_lflag = ~(ICANON|ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,term);
}

int open_preserved_screen(termios* term){
  printf(PRESERVED_SCREEN);
  term->c_lflag = (ICANON|ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,term);
}

int init(line* line_node, winsize* window){
  int i;
  for (i=0; i<window->ws_row; i++){
    line_node->text = (char*)malloc(window->ws_col);
    line_node->next = (line*)malloc(sizeof(line));
    line_node = line_node->next;
  }
  return 0;
}

int edit_file(line* line){
}

int update_display(){
}

int cleanup(line* line_node){
  while (line_node->next){
    free(line_node);
    line_node = line_node->next;
  }
  return 0;
}
