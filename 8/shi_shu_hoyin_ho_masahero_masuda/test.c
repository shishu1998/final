#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int main(){
  card* red = makedeck("red");
  card* green = makedeck("green");
  printdeck(red);
  //printdeck(green);
  shuffle(red);
  shuffle(green);
  //printdeck(red);
  //shuffle(&green);
  return 0;
}
