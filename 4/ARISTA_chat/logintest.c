#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <termios.h>
#include <unistd.h>

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
  int i,counter=0,flag=0;
  char uid[25],pwd[25],s_uid[][25]={"11user1","12user2","13user3"};
  char s_pwd[][25]={"Pwd1","Pwd2","Pwd3"},ch='a';/*dummy character in ch */
//clrscr();
  printf("\n Enter the user id : ");
  scanf("%s",uid);
  printf("\n Enter the password : ");
  i=0;
  while(1)
    {
      ch=getch();
      if(ch==13)
	break;
      else if(ch==8)
	{       if(i!=0) /*this is for avoiding the ENTER instructions getting deleted */
	    {
	      printf("\b");  /*printing backspace to move cursor 1 pos back*/
	      printf("%c",32);/*making the char invisible which is already on console*/
	      printf("\b"); /*printing backspace to move cursor 1 pos back*/
	      i--;
	      pwd[i]='\0';
	    }
	  else
	    continue;
	}
      else
	{
	  putchar('*');/* char - '*' will be printed instead of the character */
	  pwd[i]=ch;
	  i++;
	}
    }
  pwd[i]='\0';
  for(i=0;i<=2;i++)
    {
      if((strcmp(uid,s_uid[i]))==0 && (strcmp(pwd,s_pwd[i]))==0)
	{
	  flag=1;
	  break;
	}
    }
  if(flag) printf(" \n \n \t \t USER AUTHENTICATED ");
  else printf("\n \n \n\t TRESSPASSERS WILL BE SHOT AND SURVIVORS WILL BE SHOT AGAIN .. ha ha :)");
  printf("written by dileep basam .. [snipped email]");
  getch();
}
