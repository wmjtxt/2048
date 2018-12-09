 ///
 /// @file    :g2048.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2018-12-09 13:31:03
 /// @quote   :
 ///

#include"g2048.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<unistd.h>
#include<iomanip>
G2048::G2048()
{
   initPane();
}

G2048::~G2048()
{

}

void G2048::rotate90(Pane& p1,Pane& p2)
{
  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
      p2[i][j]=p1[j][i];
    }
  }
  rotate180(p2,p1);
}

void G2048::rotate_90(Pane& p1,Pane& p2)
{
   for(int i=0;i<SIZE;i++){
     for(int j=0;j<SIZE;j++){
       p2[i][j]=p1[j][i];
     }
   }
  rotate_180(p2,p1);
}

void G2048::rotate180(Pane& p1,Pane& p2)
{
  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++)
    {
      p2[i][j]=p1[i][SIZE-j-1];
    }
  }
}

void G2048::rotate_180(Pane& p1,Pane& p2)
{
  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
      p2[i][j]=p1[SIZE-i-1][j];
    }
  }
}

bool G2048::gameOver()
{
  int tmp=0;
  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
      tmp += (!pane1[i][j])?1:0;
    }
  }
  if(!tmp) return true;
  else return false;
}

bool G2048::isEmpty(int x,int y)
{
  return (!pane1[x][y])?true:false;
}

int G2048::generateNum(int x,int y)
{
    if(isEmpty(x,y)) return rand()%2?2:4;
    else return 0;
}

void G2048::initPane()
{
   srand(time(NULL));
   for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
        pane1[i][j]=0;
        pane2[i][j]=0;
     }
   }
   score=0;
}

void G2048::disPane(Pane& p)
{
    for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
        std::cout<<std::setw(4)<<p[i][j]<<' ';
      }
     std::endl(std::cout);
    }
}

void G2048::copyP1P2()
{
   for(int i=0;i<SIZE;i++){
     for(int j=0;j<SIZE;j++){
       pane1[i][j]=pane2[i][j];
     }
   }
}

void G2048::showPane(Pane& p)
{
    disPane(p);
    resetScore();
    std::cout<<"score:"<<getScore(p)<<std::endl;
}

int G2048::getScore(Pane& p)
{
   for(int i=0;i<SIZE;i++){
     for(int j=0;j<SIZE;j++){
      score+=p[i][j];
     }
   }
return score;
}

void G2048::resetScore()
{
  score=0;
}


void G2048::coreAlgorithm(Pane& p)
{
	for(int i = 0; i < SIZE; i++){
		int k = 0;
		for(int j = 0; j < SIZE; j++){
			if(p[i][j] != 0){
				p[i][k] = p[i][j];
				k++;
			}
		}
		for(int j = k; j < SIZE; j++){
			p[i][j] = 0;
		}
	}
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE-1; j++){
			if(p[i][j] == p[i][j+1]){
				p[i][j] = 2*p[i][j];
				p[i][j+1] = 0;
				j++;
			}
		}
	}
	for(int i = 0; i < SIZE; i++){
		int k = 0;
		for(int j = 0; j < SIZE; j++){
			if(p[i][j] != 0){
				p[i][k] = p[i][j];
				k++;
			}
		}
		for(int j = k; j < SIZE; j++){
			p[i][j] = 0;
		}
	}
   //for(int i=0;i<SIZE;i++){
   //  for(int j=SIZE-1;j>0;j--){
   //    if(p[i][j-1]==0){
   //       int k=j-1;
   //       for(;k<SIZE-1;k++){
   //      p[i][k]=p[i][k+1];
   //       }
   //   p[i][k]=0;
   //    }
   //    else if(p[i][j-1]==p[i][j]){
   //       p[i][j-1] *=2;
   //   int k=j;
   //   for(;k<SIZE-1;k++){
   //     p[i][k]=p[i][k+1];
   //       }
   //   p[i][k]=0;
   //    }
   //  }
   //}  
}

void G2048::handleOps(Direction& d)
{
   if(d==QUIT){
      std::cout<<"Quit!"<<std::endl;
      exit(0);
   }  
   switch(d){
     case UP:{
	  rotate_90(pane1,pane2);
	  coreAlgorithm(pane1);
	  rotate90(pane1,pane2);
	} break;
     case DOWN:{
	  rotate90(pane1,pane2);
	  coreAlgorithm(pane1);
	  rotate_90(pane1,pane2);
        }break;
     case LEFT:{
	  coreAlgorithm(pane1);
	}break;
     case RIGHT:{
	  rotate180(pane1,pane2);
	  coreAlgorithm(pane2);
	  rotate180(pane2,pane1);
	}break;
   }
}

void G2048::run()
{
  std::cout<<"game start..."<<std::endl;
  std::cout<<"-------------"<<std::endl;
  showPane(pane1);
  sleep(1);
  while(true){
  system("clear");
  if(gameOver()){
     system("clear");
     std::cout<<"-----game over-----"<<std::endl;
     showPane(pane1);
     exit(0);
  } 
  int tmpx=0;
  int tmpy=0;
  int num=0;
  do{
      tmpx=rand()%SIZE;
      tmpy=rand()%SIZE;
     num=generateNum(tmpx,tmpy);
     if(num)
       setNum(pane1,tmpx,tmpy,num);
  }while(!num);
  showPane(pane1);
  std::cout<<"---------"<<std::endl;
  std::cout<<"please enter the direction:-> | <- (w,s,a,d)"<<std::endl;
  Direction d;
  char dirt;
  while(std::cin.good()){
     std::cin.clear();
     dirt=std::cin.get();
     switch(dirt){
	case 'w':d=UP;    break;
	case 's':d=DOWN;  break;
	case 'a':d=LEFT;  break;
	case 'd':d=RIGHT; break;
	case 'q':d=QUIT;  break;
	default: d=ERR;   break;
     }
     if(d==ERR){
        char ch;
	while((ch=std::cin.get())!='\n')continue;
	std::cin.clear();
     }
     else{
        handleOps(d);
        char ch;
	while((ch=std::cin.get())!='\n')continue;
	std::cin.clear();
        break;
     }
   }
 }
  showPane(pane1);
  std::cout<<"-----------------------"<<std::endl;
  std::endl(std::cout);
}

void G2048::setNum(Pane& p,int x,int y,int num)
{
    p[x][y]=num;
} 
