#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;
#define length 20
#define width 20
#define enemynum 5
int canvas[length][width];
int score = 0;
void gotoxy(int x, int y)  //光标移动到(x,y)位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}
void show() {
	gotoxy(0, 0);
	HideCursor();
	for (int i = 0; i < length; i++) {
		for (int k = 0; k < width; k++) {
			if (canvas[i][k] == 0)
				cout << " ";
			else if (canvas[i][k] == 1)
				cout << "*";
			else if (canvas[i][k] == 2)
				cout << "@";
			else if (canvas[i][k] == 3)
				cout << "|";
		}
		cout << endl;
	}
	cout << "得分：" << score<<endl;
}

class enemy {
private:
    int enemyspeed;
	int enemy_x[enemynum];
	int enemy_y[enemynum];
public:
	enemy(int k, int x){
		enemyspeed = k;
		for(int i=0;i<enemynum;i++){
			enemy_x[i] = 1;
			enemy_y[i] = rand() % width;
		}
	}
	void fall() {
    	for (int i=0;i<length;i++){
    		for (int j=0;j<width;j++){
    			if (canvas[i][j]==3) {
    				for (int k=0;k<enemynum;k++){
    					if ((i==enemy_x[k]+1) && (j==enemy_y[k])){
    						score++;                
    						canvas[enemy_x[k]][enemy_y[k]] = 0;
    						enemy_x[k] = 1;           
    						enemy_y[k] = rand()%width;
    						canvas[enemy_x[k]][enemy_y[k]] = 1;
    						canvas[i][j] = 0;      
    					}
    				}
    			}
    		}
    	}
    }
	void speedup() {
		if (score % 5 == 0) {
			enemyspeed--;
		}
	}
	void enemydown() {
		static int speed;
		if (speed < enemyspeed)
			speed++;
		if (speed == enemyspeed)
		{
			for(int i=0;i<enemynum;i++){
				canvas[enemy_x[i]][enemy_y[i]] = 0;
	    		enemy_x[i]++;
		    	canvas[enemy_x[i]][enemy_y[i]] = 1;
	    		speed = 0;
			}
		}
	}
	void escape() {
		for(int i=0;i<enemynum;i++){
	    	if (enemy_x[i] > length) {
			    score--;
		    	enemy_x[i] = 1;
		    	enemy_y[i] = rand() % width;
	    	}
	    }
	}
	void show() {
		for(int i=0;i<enemynum;i++){
			canvas[enemy_x[i]][enemy_y[i]] = 1;
		}
	}
};
class player {
private: 
	int player_x, player_y;
public:
	player(int x, int y) :player_x(x), player_y(y) {};
	void input() {
		while (kbhit()) {
			char n = getch();
			if (n == 'w'&& player_x > 0) {
				canvas[player_x][player_y] = 0;
				player_x--;
				canvas[player_x][player_y] = 2;
			}
			else if (n == 'a'&& player_y > 0) {
				canvas[player_x][player_y] = 0;
				player_y--;
				canvas[player_x][player_y] = 2;
			}
			else if (n == 's'&&player_x < length) {
				canvas[player_x][player_y] = 0;
				player_x++;
				canvas[player_x][player_y] = 2;
			}
			else if (n == 'd'&&player_y < width) {
				canvas[player_x][player_y] = 0;
				player_y++;
				canvas[player_x][player_y] = 2;
			}
			else if (n == ' ') {
				canvas[player_x - 1][player_y] = 3;
			}

		}
	}
	void show() {
		canvas[player_x][player_y] = 2;
	}
	void lose(){
		if(canvas[player_x-1][player_y] == 1){
			cout<<"You Lose!"<<endl;
		    Sleep(2000);
	    	system("pause");
	    	exit(0);
		}
	}
};
void bulletup() {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (canvas[i][j] == 3)
			{
				canvas[i][j] = 0;
				if (i > 0)
				canvas[i-1][j] = 3;
			}
		}
	}
}
int main() {
	player me(length - 1, width / 2);
	enemy em(15, 1);
	while (1) {
		show();
		em.show();
		em.enemydown();
		em.fall();
		em.escape();
		me.show();
		me.lose();
		bulletup();
		me.input();
		Sleep(20);
	}
	return 0;
}
