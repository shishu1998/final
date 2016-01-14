//this is meant to be the file that writse a history of one's commands to a file
//will have to read the file to see if a shot fired actually hits




int storeCommand(char * name) {//keeps a log of all entered commands , whether a correct input of not
  //needed so that a command isnt entered twice
  char * entry;
  int fp;
  
  printf("\nNew contact name: ");
  // scanf("%s", &name);

  fp = open("a.txt", O_WRONLY | O_APPEND);
  write(fp, name, 256);
  close(fp);
  

 
}
