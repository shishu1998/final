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
#define CURSOR_SAVE "\033[s"
#define CURSOR_RESTORE "\033[u"
#define ALT_BUFFER "\033[?1049h\033[H"
#define PRESERVED_SCREEN "\033[?1049l"

typedef struct line {int term_line; 
  int file_offset; 
  char* text; 
  char* status;
  struct line* next;
} line;
typedef struct termios termios;
typedef struct winsize winsize;

int init(line*, winsize*);
int cleanup(line*);
int fill_buffers(int, int, line*);
int print_buffers(line*, winsize*);
int open_screen_buffer(termios*);
int open_preserved_screen(termios*);
int detect_keypress(int*, int*,line**,line**,int);
int get_cursor(int*,int*,line*,line**);
line* get_previous(int, int);
line* get_next(int, int);

static winsize global_win;

int main(){
  int cursor_row, cursor_col, read_line;
  struct termios term;
  struct winsize window;
  //ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &global_win);

  line* first_line = (line*)malloc(sizeof(line));
  line* changed_lines;
  line* current_line;

  init(first_line, &global_win);

  int map = open("./map",O_RDWR);
  fill_buffers(map,0,first_line);
  open_screen_buffer(&term);  
  print_buffers(first_line,&global_win);

  while (detect_keypress(&cursor_row,&cursor_col,&first_line,&current_line,map));

  open_preserved_screen(&term);

  cleanup(first_line);
  close(map);
}

int get_cursor(int* row, int* col, line* first_line, line** current_line){
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
  //update current_line
  int i;
  for (i=1;i<*row;i++){
    first_line = first_line->next;
  }
  *current_line = first_line;
}

int detect_keypress(int* cursor_row, int* cursor_col, line** first_line_ptr, line** current_line, int map){
  int key;
  line* first_line = *first_line_ptr;
  key = getchar();
  if (key == '\033'){
    if (getchar() == '['){
      key = getchar();
      if (key == 65){
	if (*cursor_row == 1 && first_line->file_offset > 1){//up
	  line* new_first = get_previous(map,first_line->file_offset);
	  new_first->next = first_line;
	  line* last;
	  while (first_line->next != NULL){
	  	last = first_line;
	  	first_line = first_line->next;
	  }
	  last->next = NULL;
	  free(first_line->text);
	  free(first_line);
	  *first_line_ptr = new_first;
	  first_line = *first_line_ptr;
	  printf(CURSOR_SAVE);
	  print_buffers(first_line,&global_win);
	  printf(CURSOR_RESTORE);
	}
	printf(CURSOR_UP);
	get_cursor(cursor_row, cursor_col,first_line,current_line);
      }
      else if (key == 66){
	if (*cursor_row == global_win.ws_row-1){
	  (*current_line)->next = get_next(map,(*current_line)->file_offset);
	  free(*first_line_ptr);
	  (*first_line_ptr) = first_line->next;
	  first_line = (*first_line_ptr);
	  printf(CURSOR_SAVE);
	  
	  print_buffers(first_line,&global_win);
	  printf(CURSOR_RESTORE);
	}
	else{
		printf(CURSOR_DOWN);
	}
	get_cursor(cursor_row, cursor_col,first_line,current_line);
	  }
      else if (key == 67){
	printf(CURSOR_RIGHT);
      }
      else if (key == 68){
	printf(CURSOR_LEFT);
      }
    }
  }
  else if (key == 127){//backspace
  	printf(CURSOR_LEFT);
  	printf(CURSOR_SAVE);
    get_cursor(cursor_row, cursor_col,first_line,current_line);
    (*current_line)->status = (*current_line)->text;
    char* temp = malloc(sizeof((*current_line)->text));
    strcpy(temp,(*current_line)->text);
    strcpy(&temp[*cursor_col-1],&((*current_line)->text[*cursor_col]));
    printf("\033[2K\r%s",temp);//clear line
    printf(CURSOR_RESTORE);//reset position
    (*current_line)->text = temp;
    return 1;
  }
  else if (key == 17){//ctrl+q
    return 0;
  }
  else{
    printf("%c",key);
  }
}

int fill_buffers(int file, int start_read, line* first_line){
  FILE* fstream = fdopen(dup(file),"r");
  size_t buff_size = sizeof(first_line->text); 
  first_line->file_offset = 1;
  int read = (int)getline(&first_line->text, &buff_size, fstream);
  while(first_line->next != NULL){
    first_line = first_line->next;
    first_line->file_offset = (int)ftell(fstream);
    read = (int)getline(&first_line->text, &buff_size, fstream);
    if (first_line->file_offset == -1){
      printf("%s\n",strerror(errno));
    }
  }
  fclose(fstream);
}

int print_buffers(line* first_line, winsize* window){
  //int i=1;
  while (first_line != NULL){
    //printf("%*s\r%d%s",window->ws_col,first_line->status,first_line->file_offset,first_line->text);
    printf("%*s\r%s",window->ws_col,first_line->status,first_line->text);
    first_line = first_line->next;
    //i++;
  }
  //printf("%*s",global_win.ws_col,"Control + Q to quit");
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
  for (i=1; i<window->ws_row - 1; i++){
    line_node->text = (char*)malloc(global_win.ws_col);
    line_node->next = (line*)malloc(sizeof(line));
    line_node = line_node->next;
  }
  return 0;
}

line* get_previous(int map, int next_line){//get previous line
  FILE* fstream = fdopen(dup(map),"r");
  line* first = (line*)malloc(sizeof(line));
  size_t buff_size = sizeof(first->text); 
  first->text = (char*)malloc(sizeof(global_win.ws_col));
  fseek(fstream,next_line,SEEK_SET);
  char temp;
  int off;
  while (temp != '\n' && off > 0){
    fseek(fstream,-2,SEEK_CUR);
    off = ftell(fstream);
    temp = (char)fgetc(fstream);
  }
  first->file_offset = ftell(fstream);
  getline(&first->text, &buff_size, fstream);
  fclose(fstream);
  return first;
}

line* get_next(int map, int previous_line){//get next line
  FILE* fstream = fdopen(dup(map),"r");
  line* next = (line*)malloc(sizeof(line));
  size_t buff_size = sizeof(next->text);
  next->text = (char*)malloc(sizeof(global_win.ws_col));
  fseek(fstream,previous_line,SEEK_SET);
  getline(&next->text, &buff_size, fstream);
  next->file_offset = ftell(fstream);
  getline(&next->text, &buff_size, fstream);
  next->next = NULL;
  fclose(fstream);
  return next;
}

int cleanup(line* line_node){
  while (line_node->next){
    free(line_node);
    free(line_node->text);
    free(line_node->status);
    line_node = line_node->next;
  }
  return 0;
}
