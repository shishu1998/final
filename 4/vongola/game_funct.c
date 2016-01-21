#include <stdlib.h>
#include <stdio.h>

int * assign_roles(int num_players){
  srand(time(NULL));
  //printf("%d\n",num_players);
  int r1 = rand()%num_players;
  int r2 = rand()%num_players;
  while(r2 == r1){
    r2 = rand()%(num_players);
  }
  int * role_list = (int *)malloc(num_players*sizeof(int));
  int i;
  role_list[r1] = 1;
  role_list[r2] = 1;
  return role_list;
}

int lynch_count( int i ){
  return i/2 + 1;
}

int main(){
  char* test_list[9];
  int role_list[9]={};
  int *rl = role_list;
  rl = assign_roles(9);
  int i;
  for(i = 0; i < 9; i++)
    printf("%d\n", rl[i]);
}
