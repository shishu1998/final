#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int main(){
  card* red = makedeck("red");
  card* green = makedeck("green");
  // printf("content: %s\n",red[80].content);
  //printdeck(green);
  //printdeck(green);
  shuffle(green);
  printdeck(green);
  /*int randN;
  int counter = 30;
  while (counter){
    randN=randNum()%getsize(green);
    printf("Index: %d content: %s\n",randN,green[randN].content);
    counter--;
    }*/
  //  printdeck(red);
  //shuffle(green);
  //printdeck(red);
  //shuffle(&green);
  return 0;
}
