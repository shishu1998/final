#include <fcntl.h>
#include <unistd.h>
#include <string.h>



typedef struct card{
  char* content;
  char* type;
  int owner;
}card;

typedef struct deck{
  card *cards;
  int size;
}deck;

struct card* makecard(char* content,char* type){
  card* out = (card*)malloc(sizeof(card));
  out->type = type;
  out->content = content;
  return out;
}

int randNum(){
  int descriptor = open("/dev/urandom", O_RDONLY);
  int *num = (int *)malloc(4);
  read(descriptor,num,4);
  close(descriptor);
  return *num;
}

void shuffle(deck *d){
  int rand1;
  int rand2;
  card temp;
  int counter = 0;
  while(counter < 1000){
    rand1 = randNum() % d->size;
    rand2 = randNum() % d->size;
    temp = d->cards[rand1];
    d->cards[rand1] = d->cards[rand2];
    d->cards[rand2] = temp;
    counter++;
  }
}

struct deck *makedeck(char* type){
  deck *newDeck;
  int descriptor;
  char buffer[20000];
  newDeck->size = (int)malloc(sizeof(int));
  char* maketype = (char*)malloc(sizeof("green"));
  if(type == "red"){
    descriptor = open("reddeck",O_RDONLY);
    newDeck->cards = (card*)malloc(sizeof(card)*746);
    newDeck->size=746;
    maketype = "red";
  }
  if(type == "green"){
    descriptor = open("greendeck",O_RDONLY);
    newDeck->cards = (card*)malloc(sizeof(card)*249);
    newDeck->size=249;
    maketype = "green";
  }
  read(descriptor,buffer,sizeof(buffer));
  char* cards = buffer;
  char* temp;
  int i = 0;
  while(cards){
    temp = strsep(&cards,"\n");
    newDeck->cards[i] = *makecard(temp,maketype);
    i ++;
  }
  return newDeck;
}

void printdeck(deck *d){
  int i = 0;
  while(d->cards[i].content){
    printf("%s\n",d->cards[i].content);
    i++;
  }
}


