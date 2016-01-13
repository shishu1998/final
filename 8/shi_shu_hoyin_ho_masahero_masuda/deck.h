#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct card{
  char content[100];
  char type[100];
  int owner;
}card;

card makecard(char* content,char* type){
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

card* makedeck(char* type){
  card* deck;
  int descriptor;
  char buffer[20000];
  char* maketype = (char*)malloc(sizeof("green"));
  if(type == "red"){
    descriptor = open("reddeck",O_RDONLY);
    deck = (card*)malloc(sizeof(card)*746);
    maketype = "red";
  }
  if(type == "green"){
    descriptor = open("greendeck",O_RDONLY);
    deck = (card*)malloc(sizeof(card)*249);
    maketype = "green";
  }
  read(descriptor,buffer,sizeof(buffer));
  char* temp;
  int i = 0;
  while(buffer){
    temp = strsep(&buffer,"\n");
    deck[i] = makecard(temp,maketype);
    i ++;
  }
  return deck;
}


