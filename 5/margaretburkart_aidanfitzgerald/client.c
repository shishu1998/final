#include "lib.h"
#define MAXLEN 256

void strip_add(char* source, char* dest){
  char* leftovers;
  int overall_len = strlen(source);
  
  leftovers = strchr(source,'\n');
  int leftovers_len = strlen(leftovers);
  int new_len = overall_len - leftovers_len;

  strncat(dest,source,new_len);
}

void sign_in(int socket_id){
  char use[256];
  char pass[256];
  char final[256];
  char* use_phrase = "LOGIN\nUsername: ";
  char* pass_phrase = "\nPassword: ";

  strcat(final,use_phrase);
  printf("Enter your username: ");
  fgets(use,MAXLEN,stdin);
  strip_add(use,final);

  strcat(final,pass_phrase);
  printf("Enter your password: ");
  fgets(pass,MAXLEN,stdin);
  strip_add(pass,final);

  sock_write(socket_id,final);
  printf("This is what you sent to the server:\n[%s]\n",final);
}

void choose_username(char* final, char* use){
  printf("Enter your new username: ");
  fgets(use,MAXLEN,stdin);
  strip_add(use,final);
}

void choose_password(char* final, char* pass, char* pass2, int socket_id){
  printf("Enter your new password: ");
  fgets(pass,MAXLEN,stdin);
  printf("Re-enter your new password: ");
  fgets(pass2,MAXLEN,stdin);

  if(strcmp(pass,pass2)==0){
    strip_add(pass,final);
    sock_write(socket_id,final);
  }else{
    printf("Passwords did not match. Try again:\n");
    choose_password(final, pass, pass2, socket_id);
  }
}

void sign_up(int socket_id){
  char use[256];
  char pass[256];
  char pass2[256];
  char final[256];
  char* use_phrase = "SETUP\nUsername: ";
  char* pass_phrase = "\nPassword: ";

   int i;
  i = fork();
  if(i==-1){
    printf("Error\n");
  }else if(i==0){
    int i;
    i = execlp("mkdir","mkdir","mail",NULL);
    if(i==-1){
      perror("Something went wrong!");
    }
  }else{
    strcat(final,use_phrase);
    choose_username(final, use);
    strcat(final,pass_phrase);
    choose_password(final, pass, pass2, socket_id);

    printf("This is what you sent to the server:\n[%s]\n",final);
  }
}

void check_for_account(char *buffer, int socket_id){
  if(strncmp(buffer,"y\n",2)==0){
    sign_in(socket_id);
  }else if(strncmp(buffer,"n\n",2)==0){
    sign_up(socket_id);
  }else{
    printf("Not a valid response. Enter another response: ");
    fgets(buffer,sizeof(stdin)-1,stdin);
    check_for_account(buffer, socket_id);
  }
}

void enter_mail(int socket_id){
  int i;
  for(i=0;i<10;i++){
    printf("\n");
  }
  printf("Welcome to mail!");
}


int main() {

  // Step 1. Create the socket (same as server code)
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);

  // Step 2. Bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(5000);
  // void: parses a string into a binary IP address
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  // The real action
  bind(socket_id, (struct sockaddr *) &sock, sizeof(sock));

  // Step 3. Attempt to create a connection
  // i is a message
  int i = connect(socket_id, (struct sockaddr *) &sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);

  // Step 4. Do network stuff
  char buffer[256];
  //read(socket_id, buffer, sizeof(buffer) - 1);
  
  //Request info from user
  printf("Do you already have an account? (y/n)\n");
  //read info
  fgets(buffer,sizeof(stdin)-1,stdin);
  check_for_account(buffer, socket_id);
  
  return 0;

  
}
