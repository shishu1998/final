#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int main(){
  card* red = makedeck("red");
  card* green = makedeck("green");
  //printdeck(green);
  shuffle(red);
  printdeck(red);
  //  shuffle(green);
  //printdeck(red);
  //shuffle(&green);
  return 0;
}
