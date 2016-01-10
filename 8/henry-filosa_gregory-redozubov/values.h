#ifndef values
#define values

/*Input formats:
  ? - displays command formats
  msg [name] [msg] - Sends message to [name]
  file [name] [filename] - Sends file to [name]
  com [name] [command] - Sends command to [name]
  old [name] - retrieve old messages from [name]
*/

//This is the information that is sent before the data to prepare server for receiving it
typedef struct base{
  char type;
  char dest[30];
  char sender[30];
  int size;
}base;

char * help="You have the following commands:\n\t1 - Send a message\n\t2 - Send a file\n\t3- Send a command";

#define MAXRCVLEN 500
#define PORTNUM 2300
#define NAME_LEN 21
#define PASS_LEN 21

#endif
