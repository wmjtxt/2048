 ///
 /// @file    :main.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2018-12-09 16:16:25
 /// @quote   :
 ///
 
#include "wmj2048.h"
/*
void initialize() {
    // ncurses初始化
    initscr();
    // 按键不需要输入回车直接交互
    cbreak();
    // 按键不显示
    noecho();
    // 隐藏光标
    curs_set(0);
    // 随机数
    srand(time(NULL));
}
void shutdown() {
    // ncurses清理
    endwin();
}
*/

int main(){
    //initialize();
	W2048 w;
	w.run();
    //shutdown();
	return 0;
}
