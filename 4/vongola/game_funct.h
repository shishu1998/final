//--------ROLES----------
#define TOWNIE 0
#define MAFIASO 1
#define DOCTOR 2
#define COP 3

//-------STATUS----------
#define DEAD 0
#define ALIVE 1

//-------VOTE------------
#define NO 0
#define YES 1

typedef struct player{
  char name[256];
  int role;
  int fd;
  int status;
  int vote;
}
  player;

void assign_roles(player** player_list);
int lynch_count(int i);
void shuffle(player** player_list);
