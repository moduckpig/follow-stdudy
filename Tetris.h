#pragma once
#include <vector>
#include "Block.h"
#include "Ranklist.h"
using namespace std;
enum MenuItem {
	MENU_START,
	MENU_PAUSE,
	MENU_RANK,
	MENU_EXIT,
	MENU_MAX,
};
class Tetris
{
public:
	Tetris(int rows, int left, int bottom, int cols,int blocksize);
	void init();
	void startplay();
	void drop();
	void saveblock(Block* block);
	void dropblock();
	void reverseblock();
	void handlemenu();
	void drawmenu();
	void showrank();
	void pausegame();
	static int getscore() { return score; }
	int getlevel() const { return level; }

	
private:
	void keyevent();
	void drawboard();
	int getdelay();
	void lendclear();
	void drawnextblock();
	bool island(Block* block);
	void dropbottom();
	bool iscollide(Block* block);
	void updatalevelandspeed();
	bool windowfull();

private:
	int delay; // 添加 delay 成员变量，单位可根据需要调整（如毫秒）
    bool updata = false; 
	int timer = 0;
	int rows;
	int left;
	int bottom;
	int cols;
	int blocksize;
	vector<vector<int>> map;
	vector<vector<COLORREF>>colormap;
	Block* nowblock=nullptr;
	Block* nextblock=nullptr;
	const int NEXT_X = 500;
	const int NEXT_Y = 50;
	Block bakblock;
	static int score ;
	int linecount = 0;
	int level = 1;
	bool paused = false;
	bool gameover = false;
	const int MENU_HEIGHT = 30;
	const TCHAR* menutexts[MENU_MAX] = { _T("开始游戏"),_T("暂停游戏"),_T("排行榜"),_T("退出游戏") };
	Ranklist ranklist;
	bool started = false;
};


