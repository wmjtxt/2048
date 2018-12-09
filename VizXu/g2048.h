 ///
 /// @file    :g2048.h
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2018-12-09 13:30:24
 /// @quote   :
 ///

#ifndef _G2048_
#define _G2048_
#include "panel.h"
class G2048
{
public:
   G2048();
   ~G2048();
private:
   Pane pane1;
   Pane pane2;
   int  score;
private:
   void initPane();
   void disPane(Pane&);
   void copyP1P2();
   bool isEmpty(int,int);
   int  generateNum(int,int);
   bool gameOver();
   void rotate90(Pane&,Pane&);
   void rotate_90(Pane&,Pane&);
   void rotate180(Pane&,Pane&);
   void rotate_180(Pane&,Pane&);
   int  getScore(Pane&);
   void resetScore();
   void setNum(Pane&,int,int,int);
   void handleOps(Direction&);
private:
   void coreAlgorithm(Pane&);
public:
   void showPane(Pane&);
   void run();
};
#endif //g2048.h 
