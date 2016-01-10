#ifndef server
#define server

void listen_struct();
/*======== void listen_struct() ==========
  Inputs: struct base 
  Returns: 
  Listens to data stream for base struct
  ====================*/

void listen_data();
/*======== void listen_data() ==========
  Inputs: buf[]
  Returns: 
  Listens to data stream for data that follows base struct
  ====================*/

#endif
