#ifndef client
#define client

/*Input formats:
  ? - displays command formats
  msg [name] [msg] - Sends message to [name]
  file [name] [filename] - Sends file to [name]
  com [name] [command] - Sends command to [name]
  old [name] - retrieve old messages from [name]
*/

typedef struct base{
  char type;
  char dest[30];
  char sender[30];
  int size;
}base;

Int process();
/*======== Int process() ==========
  Inputs:  char[] command
  Returns: Boolean
  Processes command and breaks into components. Returns 0 if invalid command.
  ====================*/

struct package():
/*======== Void package() ==========
  Inputs: char[]
  Returns: struct *
  ====================*/

#endif
