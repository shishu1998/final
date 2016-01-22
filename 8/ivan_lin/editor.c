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

typedef struct line {int term_line; int file_line; char* text; struct line* next;} line;
typedef struct termios termios;
typedef struct winsize winsize;

int init(line*, winsize*);
int cleanup(line*);
int fill_buffers(int, int, line*);
int print_buffers(line*);
int open_screen_buffer(termios*);
int open_preserved_screen(termios*);
int detectKeyPress();

int main(){
  int cursor_row, cursor_col, read_line;
  struct termios term;
  struct winsize window;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

  line* first_line = (line*)malloc(sizeof(line));
  init(first_line, &window);

  int map = open("./map",O_RDONLY);

  fill_buffers(map,0,first_line);
  
  print_buffers(first_line);

  open_screen_buffer(&term);
  print_buffers(first_line);

  int i;
  while (detectKeyPress()){
    //detectKeyPress();
    //fflush(stdout);
    //sleep(1);
  }
  open_preserved_screen(&term);

  cleanup(first_line);
  close(map);
}

int detectKeyPress(){
  //UP:27,91,65
  //DOWN:27,91,66
  //LEFT:27,91,68
  //RIGHT:27,91,67
  int key;
  key = getchar();
  if (key == '\033'){
    if (getchar() == '['){
      key = getchar();
      if (key == 65){
	//UP
      }
      if (key == 66){
	//DOWN
      }
      if (key == 67){
	//RIGHT
      }
      if (key == 68){
	//LEFT
      }
    }
  }
  else if (key == 17){//ctrl+q
    return 0;
  }
  return 1;
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
  
int print_buffers(line* first_line){
  while (first_line->next){
    printf("%s",first_line->text);
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

int cleanup(line* line_node){
  while (line_node->next){
    free(line_node);
    line_node = line_node->next;
  }
  return 0;
}
