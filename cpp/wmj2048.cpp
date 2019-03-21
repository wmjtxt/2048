 ///
 /// @file    :wmj2048.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2018-12-09 15:14:21
 /// @quote   :
 ///
 
#include "wmj2048.h"

W2048::W2048(){
	initPane();
}

W2048::~W2048(){}

void W2048::initPane(){
	srand(time(NULL));
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			pane1[i][j] = 0;
			pane2[i][j] = 0;
		}
	}
	score = 0;
}

void W2048::disPane(Pane& p){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			cout << setw(4) << p[i][j] << ' ';
		}
		cout << endl;
	}
}

void W2048::copyP1P2(){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			pane1[i][j] = pane2[i][j];
		}
	}
}

bool W2048::isEmpty(int x, int y){
	return (!pane1[x][y]) ? true : false;
}

int W2048::generateNum(int x, int y){
	if(isEmpty(x,y))
		return rand()%10 == 1 ? 4 : 2;//
	else 
		return 0;
}

bool W2048::gameOver(){
	int tmp = 0;
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			tmp += (!pane1[i][j]) ? 1 : 0;
		}
	}
	if(!tmp) return true;
	else return false;
}

int W2048::getScore(Pane& p){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			score += p[i][j];
		}
	}
	return score;
}

void W2048::resetScore(){
	score = 0;
}

void W2048::setNum(Pane& p, int x, int y, int num){
	p[x][y] = num;
}


void W2048::handleOps(Direction& d){
	if(d == QUIT){
		cout << "Quit!" << endl;
		exit(0);
	}
	switch(d){
		case UP : computeUp(pane1); break;
		case DOWN : computeDown(pane1); break;
		case LEFT : computeLeft(pane1); break;
		case RIGHT : computeRight(pane1); break;
	}
}

void W2048::computeLeft(Pane& p){
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
}

void W2048::computeRight(Pane& p){
	for(int i = 0; i < SIZE; i++){
		int k = SIZE-1;
		for(int j = SIZE-1; j >= 0; j--){
			if(p[i][j] != 0){
				p[i][k] = p[i][j];
				k--;
			}
		}
		for(int j = k; j >= 0; j--){
			p[i][j] = 0;
		}
	}
	for(int i = 0; i < SIZE; i++){
		for(int j = SIZE-1; j > 0; j--){
			if(p[i][j] == p[i][j-1]){
				p[i][j] = 2*p[i][j];
				p[i][j-1] = 0;
				j--;
			}
		}
	}
	for(int i = 0; i < SIZE; i++){
		int k = SIZE-1;
		for(int j = SIZE-1; j > 0; j--){
			if(p[i][j] != 0){
				p[i][k] = p[i][j];
				k--;
			}
		}
		for(int j = k; j >= 0; j--){
			p[i][j] = 0;
		}
	}
}


void W2048::computeUp(Pane& p){
	for(int i = 0; i < SIZE; i++){
		int k = 0;
		for(int j = 0; j < SIZE; j++){
			if(p[j][i] != 0){
				p[k][i] = p[j][i];
				k++;
			}
		}
		for(int j = k; j < SIZE; j++){
			p[j][i] = 0;
		}
	}
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE-1; j++){
			if(p[j][i] == p[j+1][i]){
				p[j][i] = 2*p[j][i];
				p[j+1][i] = 0;
				j++;
			}
		}
	}
	for(int i = 0; i < SIZE; i++){
		int k = 0;
		for(int j = 0; j < SIZE; j++){
			if(p[j][i] != 0){
				p[k][i] = p[j][i];
				k++;
			}
		}
		for(int j = k; j < SIZE; j++){
			p[j][i] = 0;
		}
	}
}

void W2048::computeDown(Pane& p){
	for(int i = 0; i < SIZE; i++){
		int k = SIZE-1;
		for(int j = SIZE-1; j >= 0; j--){
			if(p[j][i] != 0){
				p[k][i] = p[j][i];
				k--;
			}
		}
		for(int j = k; j >= 0; j--){
			p[j][i] = 0;
		}
	}
	for(int i = 0; i < SIZE; i++){
		for(int j = SIZE-1; j > 0; j--){
			if(p[j][i] == p[j-1][i]){
				p[j][i] = 2*p[j][i];
				p[j-1][i] = 0;
				j--;
			}
		}
	}
	for(int i = 0; i < SIZE; i++){
		int k = SIZE-1;
		for(int j = SIZE-1; j >= 0; j--){
			if(p[j][i] != 0){
				p[k][i] = p[j][i];
				k--;
			}
		}
		for(int j = k; j >= 0; j--){
			p[j][i] = 0;
		}
	}
}

void W2048::showPane(Pane& p){
	disPane(p);
	resetScore();
	cout << "score:" << getScore(p) << endl;
}

void W2048::run(){
	system("clear");
	//showPane(pane1);
	//sleep(1);
	while(true){
		system("clear");
		if(gameOver()){
			cout << "-----game over-----" << endl;
			showPane(pane1);
			exit(0);
		}
		int tmpx = 0, tmpy = 0, num = 0;
		while(!num){
			tmpx = rand()%SIZE;
			tmpy = rand()%SIZE;
			num = generateNum(tmpx,tmpy);
			if(num)
				setNum(pane1,tmpx,tmpy,num);
		}
		showPane(pane1);
		cout << "Please enter the direction:(w,s,a,d)" << endl;
		Direction d;
		char dirt;
		while(cin.good()){
			cin.clear();
			dirt = cin.get();
			switch(dirt){
				case 'w':d = UP;	break;
				case 's':d = DOWN;	break;
				case 'a':d = LEFT;	break;
				case 'd':d = RIGHT;	break;
				case 'q':d = QUIT;	break;
				default :d = (Direction)ERR;	break;
			}
			if(d == ERR){
				char ch;
				while((ch = cin.get()) != '\n') continue;
				cin.clear();
			}
			else{
				handleOps(d);
				char ch;
				while((ch = cin.get()) != '\n') continue;
				cin.clear();
				break;
			}
		}
	}
}
