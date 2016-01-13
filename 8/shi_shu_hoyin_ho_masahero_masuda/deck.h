#include <fcntl.h>
#include <unistd.h>

typedef struct card{
  char content[100];
  char type[100];
  int owner;
}card;

int randNum(){
  int descriptor = open("/dev/urandom", O_RDONLY);
  int *num = (int *)malloc(4);
  read(descriptor,num,4);
  close(descriptor);
  return *num;
}

void shuffle(card deck[]){
  int len = sizeof(deck)/sizeof(card);
  int rand1;
  int rand2;
  card temp;
  int counter = 0;
  while(counter < 1000){
    rand1 = randNum() % len;
    rand2 = randNum() % len;
    temp = deck[rand1];
    deck[rand1] = deck[rand2];
    deck[rand2] = temp;
  }
}

card* makedeck(){
}


