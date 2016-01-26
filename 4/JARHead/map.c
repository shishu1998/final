#include "map.h"

void init(char* map) {
  memset(map, 0, sizeof(map));
  int i;
  for (i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i) {
<<<<<<< HEAD
    strcat(map, " ");
=======
    strcat(map, "-");
>>>>>>> f77fcc45a5b5d702d0a2e4f4875a235af0fcc1ac
  }
}

void display_printf(char* map) {
  int i;
  for (i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i) {
    if (i % MAP_WIDTH == 0 && i) {
      printf("\n");
    }
    printf("%c", map[i]);
  }
  printf("\n");
}

void display_printw(char* map) {
  int i;
  for (i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i) {
    if (i % MAP_WIDTH == 0 && i) {
      printw("\n");
    }
    printw("%c", map[i]);
  }
  printw("\n");
}
<<<<<<< HEAD
=======

int index_to_x(int index) {
  return index % MAP_WIDTH;
}

int index_to_y(int index) {
  return index / MAP_WIDTH;
}

int index_of(char* map, char c) {
  return (int) (strchr(map, c) - map);
}

int coord_to_index(int x, int y) {
  return x + (y * MAP_WIDTH);
}

void add_new_player(char* map, char player) {
  int coord = coord_to_index(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
  while (map[coord] != '-') {
    coord = coord_to_index(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
  }
  map[coord] = player;
}

void move_player(char* map, char player, int up, int left) {
  int index = (int) (strchr(map, player) - map);
  int x = index_to_x(index) + left;
  int y = index_to_y(index) + up;
  int newIndex = coord_to_index(x, y);
  if (newIndex >= 0 && newIndex < MAP_WIDTH * MAP_HEIGHT) {
      map[newIndex] = player;
      map[index] = ' ';
  }
}

void update(char* map) {
}
>>>>>>> f77fcc45a5b5d702d0a2e4f4875a235af0fcc1ac
