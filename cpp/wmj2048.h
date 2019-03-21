 ///
 /// @file    :wmj2048.h
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2018-12-09 15:15:57
 /// @quote   :
 ///
 
#ifndef _WMJ2048_
#define _WMJ2048_

#include "panel.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
#include <curses.h>

using namespace std;

class W2048{
public:
	W2048();
	~W2048();
private:
	Pane pane1;
	Pane pane2;
	int score;
private:
	void initPane();
	void disPane(Pane&);
	void copyP1P2();
	bool isEmpty(int,int);
	int generateNum(int,int);
	bool gameOver();
	int getScore(Pane&);
	void resetScore();
	void setNum(Pane&,int,int,int);
	void handleOps(Direction&);
private:
	void computeLeft(Pane&);
	void computeRight(Pane&);
	void computeUp(Pane&);
	void computeDown(Pane&);
public:
	void showPane(Pane&);
	void run();
};
#endif //wmj2048.h
