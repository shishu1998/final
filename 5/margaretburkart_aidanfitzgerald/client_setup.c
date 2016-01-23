#include "lib.h"

int main() {

  // Make my_mail directory
  // Needs to be rwx* so that we can cd into it
  mkdir("my_mail.d", 0744);
  mkdir("my_mail.d/Inbox.d",0744);
  mkdir("my_mail.d/Sent.d",0744);
  mkdir("my_mail.d/Drafts.d",0744);

  return errno;
}
