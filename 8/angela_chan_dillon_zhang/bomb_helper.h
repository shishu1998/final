#ifndef _BOMB_HELPER_H_
#define _BOMB_HELPER_H_

typedef struct module {
  int complete;
  int steps;
  int current_step;
  char** visual_representation;
} module;

int create_random();

void draw_bomb();

int verify_input(char* input, module** m);

module *create_module(char* filename);

void print_module(module *m);

int verify_module(module *m, char *input);

int completed_module(module *m);

int completed_game(module **m);
#endif 
