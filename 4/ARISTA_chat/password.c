#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

int main(int argc, char **argv)
{
        char passwd[16];
        char *in = passwd;
        struct termios  tty_orig;
        char c;
        tcgetattr( STDIN_FILENO, &tty_orig );
        struct termios  tty_work = tty_orig;

        puts("Please input password:");
        tty_work.c_lflag &= ~( ECHO | ICANON );  // | ISIG );
        tty_work.c_cc[ VMIN ]  = 1;
        tty_work.c_cc[ VTIME ] = 0;
        tcsetattr( STDIN_FILENO, TCSAFLUSH, &tty_work );

        while (1) {
                if (read(STDIN_FILENO, &c, sizeof c) > 0) {
                        if ('\n' == c) {
                                break;
                        }
                        *in++ = c;
                        write(STDOUT_FILENO, "*", 1);
                }
        }

        tcsetattr( STDIN_FILENO, TCSAFLUSH, &tty_orig );

        *in = '\0';
        fputc('\n', stdout);

        // if you want to see the result: 
 printf("Got password: %s\n", passwd);

        return 0;
}
