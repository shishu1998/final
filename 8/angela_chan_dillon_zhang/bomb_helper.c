#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "bomb_helper.h"

int create_random() {
  int dev_des = open("/dev/random", O_RDONLY);
  int random_num;
  read(dev_des, &random_num, 4);
  return abs(random_num);
}

void draw_bomb() {
  int age = fork();
  if (age) {
    int information;
    int waiting = wait(&information);
  } else {
    execlp("cat", "cat", "asciiart/bomblayout.dat", NULL);
  }
}

int verify_input(char* input, module** m) {
  char* okay[5] = {"1", "2", "3", "4", "5"};
  int counter = 0;
  while (counter < 5) {
    if (!strcmp(okay[counter], input)) {
      if (!m[counter]->complete){
	return counter;
      } else {
	printf("\n\n\nModule has been already completed or is currently unavaiable.\n");
	return -1;
      }
    }
    counter++;
  }
  if (!strcmp(input, "exit")) {
    printf("\n\n\nGiving up is the same as losing!\n");
    return -2;
  }
  printf("\n\n\nBad input, please try again.\n");
  return -1;
}

module* create_module(char* filename) {
  module *m = (module *)malloc(sizeof(module));
  
  int input_status = open(filename, O_RDONLY);
  if (input_status < 0) {
    printf("ERROR: %s",strerror(errno));
    exit(1);
  }

  char *temp = (char *)malloc(sizeof(char)*49152);
  int reader = read(input_status, temp, 49152);
  if (reader < -1) {
    printf("Error: %s\n", strerror(errno));
    exit(1);
  }

  m->complete = 0;

  int counter = 0;
  char** lines = (char**)malloc(sizeof(char)*49152); 
  while (temp) {
    lines[counter] = strsep(&temp, "\n");
    counter++;
  }

  m->steps = atoi(lines[0]); 
  m->current_step = 0;
  m->visual_representation = lines;
  return m;
}

void print_module(module *m) {
  int displacement = 2 + m->current_step * 28;
  int counter = 0;
  while (counter < 27) {
    printf("%s\n",m->visual_representation[displacement+counter]);
    counter++;
  }
}

int verify_module(module *m, char *input) {
  if ( !strcmp(m->visual_representation[2 + 27 + m->current_step * 28], input) ) {
    m->current_step++;
    return 1;
  } else {
    return 0;
  }
}

int completed_module(module *m) {
  if (m->current_step == m->steps) {
    m->complete = 1;
    return 1;
  } else {
    return 0;
  }
}

int completed_game(module **m) {
  int counter = 0;
  while(counter < 2) {
    if (!completed_module(m[counter])) {
      return 0;
    }
    counter++;
  }
  return 1;
}
