#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int main(){
  card* red = (card *)malloc(sizeof(card)*746);
  red =  makedeck("red");
  card* green = makedeck("green");
  // printf("content: %s\n",red[80].content);
  printdeck(red);
  //printdeck(green);
  //shuffle(red);
  /* int randN;
  int counter = 30;
  while (counter){
    randN=randNum()%getsize(red);
    printf("Index: %d content: %s\n",randN,red[randN].content);
    counter--;
    }*/
  //  printdeck(red);
  //shuffle(green);
  //printdeck(red);
  //shuffle(&green);
  return 0;
}
