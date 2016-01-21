#include "lib.h"

void sign_in(int socket_id){
  char buff[256];
  char *buffer = buff;
  char buff1[256];
  char *buffer1 = buff;
  char *final = "LOGIN\nUsername: ";

  printf("Enter username: ");
  fgets(buffer,sizeof(stdin)+1,stdin);
  strcat(final,buffer);
  
  char *sep = "\nPassword: ";
  strcat(final,sep);

  printf("Enter password: ");
  fgets(buffer1,sizeof(stdin)+1,stdin);
  strcat(final,buffer);

  write(socket_id, final, sizeof(final) -1);
}

void choose_username(char* final, char* buffer){
  printf("Enter your new username: ");
  fgets(buffer,sizeof(stdin)-1,stdin);
  printf("Successfully read from stdin\n");
  strncat(final,buffer,12);
  printf("Successfully used strcat\n");
  
  char *sep = "\nPassword: ";
  strcat(final,sep);
}

void choose_password(char* final, char* buffer1, char* buffer2, int socket_id){
  printf("Enter your new password: ");
  fgets(buffer1,sizeof(stdin)-1,stdin);
  printf("Re-enter your new password: ");
  fgets(buffer2,sizeof(stdin)-1,stdin);

  if(strcmp(buffer1,buffer2)==0){
    strcat(final,buffer2);
    write(socket_id, final, sizeof(final) -1);
  }else{
    printf("Passwords did not match. Try again:\n");
    choose_password(final, buffer1, buffer2, socket_id);
  }
}

void sign_up(int socket_id){
  char buff[256];
  char *buffer = buff;
  char buff1[256];
  char *buffer1 = buff;
  char buff2[256];
  char *buffer2 = buff;
  char *final = "SETUP\nUsername: ";

  int i;
  i = fork();
  if(i==-1){
    //return errno;
  }else if(i==0){
    execl("mkdir","mkdir","mail");
    //return 0;
  }else{
    //int exit;
    //int pid = wait(&exit);
    //return WEXITSTATUS(exit);
    //choose_username(final, buffer);
    //choose_password(final, buffer1, buffer2, socket_id);
    choose_username(final, buffer);
    choose_password(final, buffer1, buffer2, socket_id);
  }
}

void check_for_account(char *buffer, int socket_id){
  if(strncmp(buffer,"y\n",2)==0){
    sign_in(socket_id);
  }else if(strncmp(buffer,"n\n",2)==0){
    sign_up(socket_id);
  }else{
    printf("Not a valid response.");
  }
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
  printf("Successfully read from stdin\n");
  //buffer = strsep(&pin, args);
  check_for_account(buffer, socket_id);
  
  return 0;

  
}
