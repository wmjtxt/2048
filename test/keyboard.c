 ///
 /// @file    :keyboard.c
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2018-12-09 16:55:12
 /// @quote   :
 ///
 
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>
void setBufferedInput(bool enable) {
static bool enabled = true;
static struct termios old;
struct termios new;
if (enable && !enabled) {
// restore the former settings
tcsetattr(STDIN_FILENO,TCSANOW,&old);
// set the new state
enabled = true;
} else if (!enable && enabled) {
// get the terminal settings for standard input
tcgetattr(STDIN_FILENO,&new);
// we want to keep the old setting to restore them at the end
old = new;
// disable canonical mode (buffered i/o) and local echo
new.c_lflag &=(~ICANON & ~ECHO);
// set the new settings immediately
tcsetattr(STDIN_FILENO,TCSANOW,&new);
// set the new state
enabled = false;
}
}

int main(int argc, char *argv[]) {
char c;
setBufferedInput(false);
while(true){
c=getchar();
switch(c){
case 68:
printf("%c",c);
break;
}
printf("%c",c);
}
return 0;
}
