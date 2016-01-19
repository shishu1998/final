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
int print_selection(int file, winsize* window, int start_read){
  FILE* fstream = fdopen(file,"r");
  char *buffer = malloc((*window).ws_col);
  ssize_t buff_size = sizeof(buffer);

  int read;
  
  read = getline(&buffer, &buff_size, fstream);
  
  free(buffer);
}

int open_screen_buffer(){
  printf(ALT_BUFFER);
}

int open_preserved_screen(){
  printf(PRESERVED_SCREEN);
}

int init(line* line_node, winsize* window){
  int i;
  for (i=0; i<(*window).ws_row; i++){
    (*line_node).text = malloc((*window).ws_col);
    (*line_node).next = malloc(sizeof(line));
    line_node = (*line_node).next;
  }
  return 0;
}

int cleanup(line* line_node){
  while ((*line_node).next){
    free(line_node);
    line_node = (*line_node).next;
  }
  return 0;
}

int main(){
  int cursor_row, cursor_col, read_line;

  struct winsize window;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

  line* first_line = (line*)malloc(sizeof(line));
  init(first_line, &window);

  int map = open("./map",O_RDONLY);

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
