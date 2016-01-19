#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define CURSOR_UP "\033[1A"
#define CURSOR_DOWN "\033[1B"
#define CURSOR_RIGHT "\033[1C"
#define CURSOR_LEFT "\033[1D"
#define ALT_BUFFER "\033[?1049h\033[H"
#define PRESERVED_SCREEN "\033[?1049l"

typedef struct line {int term_line; int file_line; char* text; struct line* next;} line;
typedef struct winsize winsize;

int init(line*, winsize*);
int cleanup(line*);
int fill_buffers(int, int, line*);
int print_buffers(line*);
int open_screen_buffer();
int open_preserved_screen();

int main(){
  int cursor_row, cursor_col, read_line;

  struct winsize window;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

  line* first_line = (line*)malloc(sizeof(line));
  init(first_line, &window);

  int map = open("./map",O_RDONLY);

  fill_buffers(map,0,first_line);
  
  open_screen_buffer();
  while (1){
    printf("HI YALL");
    fflush(stdout);
    sleep(1);
  }
  open_preserved_screen();
  
  cleanup(first_line);
  close(map);
}

int fill_buffers(int file, int start_read, line* first_line){
  FILE* fstream = fdopen(file,"r");
  size_t buff_size = sizeof((*first_line).text); 
  printf("%d\n",buff_size);
  int read;
  read = (int)getline(&(*first_line).text, &buff_size, fstream);
}
  
int print_buffers(line* first_line){
  while (first_line->next){
    printf("%s\n",first_line->text);
    first_line = first_line->next;
  }
}

int open_screen_buffer(){
  printf(ALT_BUFFER);
}

int open_preserved_screen(){
  printf(PRESERVED_SCREEN);
}

int init(line* line_node, winsize* window){
  int i;
  for (i=0; i<4; i++){
    //for (i=0; i<window->ws_row; i++){
    line_node->text = (char*)malloc(window->ws_col);
    printf("cols: %d, actually: %d",window->ws_col,(int)sizeof());
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
