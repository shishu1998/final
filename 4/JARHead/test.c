/**
 * Test file.
 */

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

#include "map.h"

int main(int c, char** argv) {

  char map[4096];
  init(map);
  add_new_player(map, 'a');

  printf("%d %d\n", index_to_x(64), coord_to_index(0, 0));

  display_printf(map);

  move_player(map, 'a', 1, 1);

  printf("\n");

  display_printf(map);

  return 0;
}
