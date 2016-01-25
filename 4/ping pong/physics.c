#include <stdio.h>
#include <stdlib.h>
#include "physics.h"

//Initializes a coordinate system of height*width character blocks
//For each unit of height and width, charheight*charwidth is allocated based on physics.h
char** createCoordinateSpace(height, width){
  char** origin = malloc(sizeof(char*)*width*charwidth);
  int c;
  for(c=0;c<width;c++){
    origin[c] = malloc(sizeof(char)*height*charheight);
  }
  return origin;
}

char searchBlock(char** origin, coordinate pair){
  int myx, myy;
  int xmax = pair->x+charwidth;
  int ymax = pair->y+charheight;
  for(myx = pair->x;myx<xmax;myx++){
    for(myy = pair->y;myy<ymax;myy++){
      
    }
  }
}

void displayCoordinateSpace(char** origin, length, width){
  int x,y;
  for(x=0;x<width,x++){
    for{y=0;y<length;y++){
      char node = origin[x][y];
      if(node){ //If a ball is encountered, will display a B
	if(node="b"){
	  printf("O");
	}else if(node="p"){
	  printf("#");
	}else{
	  printf(" ");
	}	
      }
    }
  }
}
