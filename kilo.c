#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);

}

void enableRawMode() {
    // Get terminal attributes
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode); // reset terminal when program exits

    // Edit terminal attributes
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_lflag &= ~(ECHO   | ICANON | IEXTEN | ISIG);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= ~(CS8);
    raw.c_cc[VMIN]  = 0; // min bytes       for read() to return = 0
    raw.c_cc[VTIME] = 1; // max /10ths secs for read() to return = 1

    // Set terminal attributes
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void) {
    enableRawMode();

    while(1) {
        char c = '\0'; // initalise to NULL ASCII to ensure no garbage value is passed to later funtions if read() returns 0
        read(STDIN_FILENO, &c, 1);

        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%c = %d\r\n", c, c);
        }

        if (c == 'q') {
            break;
        }
    }

    return 0;
}