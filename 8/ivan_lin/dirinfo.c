#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int read_top_level(char *path){
  DIR *dir;

  dir = opendir(path);
 
  struct dirent *dir_file;
  struct stat file;
  
  int map_file = open("map",O_WRONLY|O_CREAT,0777);
  dup2(map_file, 1);
  
  char name[256];
  
  dir_file = readdir(dir);
  
  while (dir_file){
    strcpy(name, path);
    strcat(name, dir_file->d_name);
    stat(dir_file->d_name, &file);
    if (S_ISDIR(file.st_mode)){
      //file is directory
    }else{
      //file is file
    }
    dir_file = readdir(dir);

    printf("%s\n",name);
  }
 
  close(map_file);
  closedir(dir);
}

int directTo(int newfd){
  int newout = dup(1);
  int temp = dup2(newfd, 1);
  
}

int main( int argc, char *argv[] ){
  if (argv[1] == NULL){
    read_top_level("./");
  }else{
      read_top_level(argv[1]);
  }
}
