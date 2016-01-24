#define TOWNIE 0
#define MAFIASO 1
#define DOCTOR 2
#define COP 3

typedef struct player{
  char name[256];
  int role;
  int fd;
}
  player;

void assign_roles(player** player_list);
int lynch_count(int i);
void shuffle(player** player_list);
