#define _WIN32_WINNT 0x0600
#include <Windows.h>
#include "Tetris.h"
#include <cstdlib> 
#include <ctime>   
#include <easyx.h>
#include <conio.h>
#include <iostream>
using namespace std;
int Tetris::score = 0;

const int speed_normal = 500;
const int speed_fast = 50;
Tetris::Tetris(int rows, int left, int bottom, int cols, int blocksize)
{
	this->rows = rows;
	this->left = left;
	this->bottom = bottom;
	this->cols = cols;
	this->blocksize = blocksize;
	this->delay = 100; 
	for (int i = 0; i < rows; i++) {
		vector<int>maprow;
		for (int j = 0; j < cols; j++) {
			maprow.push_back(0);//构建一维数组；
		}
		map.push_back(maprow);//构建二维数组；
		vector<COLORREF>colorrow(cols, BLACK);
		colormap.push_back(colorrow);
	}
}

void Tetris::init()
{
	delay = speed_normal;
	srand(static_cast<unsigned int>(time(NULL)));
	initgraph(680, 500);
	setbkcolor(BLACK);
	cleardevice();
	SetForegroundWindow(GetHWnd());
	SetFocus(GetHWnd());
}

void Tetris::startplay()
{
	init();
	nowblock = nullptr;
	nextblock = nullptr;
	while (true) {
		handlemenu();
		keyevent();
		if (paused) {
			pausegame();
			paused = false;
			updata = true;
		}
		if (gameover) {
			settextcolor(RED);
			settextstyle(36, 0, _T("宋体"));
			outtextxy(200, 200, _T("游戏失败"));
			TCHAR finalscore[50];
			swprintf_s(finalscore, _T("最终分数为：%d"), score);
			outtextxy(200, 250, finalscore);
			outtextxy(200, 300, _T("点击排行版提交成绩"));
			FlushBatchDraw();
			if (MessageBox(NULL, _T("是否提交当前成绩到排行榜？"), _T("游戏结束"), MB_YESNO == IDYES)) {
				showrank();
			}
			gameover = false;
			Sleep(100);
			continue;
		}
		//间隔时间控制，实现方块下降；
		if (started) {
			timer += getdelay();
			if (timer > delay) {
				//方块下降；
				drop();//怎么让能让我在这里调用block类的drop函数呢？？;
				timer = 0;
				updata = true;
			}
		} 
		if (updata) {//更新游戏界面；
			drawmenu();
			if (started) {
				drawboard();
				lendclear();//清除满行;
			}
			updata = false;
		}
	}
}

void Tetris::keyevent()//玩家输入
{
	if (GetAsyncKeyState(VK_SPACE) & 0X8000) {
		dropbottom();
		updata = true;
		Sleep(150);
		return;
	}
	else if (GetAsyncKeyState(27) & 0X8000) {
		exit(0);
		return;
	}
	else if ( GetAsyncKeyState(VK_LEFT) & 0X8000) {
		bakblock = *nowblock;
		nowblock->offsetX -= 1;
		if (iscollide(nowblock))nowblock->stock(bakblock);
		drawboard();
		updata = true;
		Sleep(50);
	}
	else if ( GetAsyncKeyState(VK_RIGHT) & 0X8000) {
		bakblock = *nowblock;
		nowblock->offsetX += 1;
		if (nowblock->offsetX > 19) {
			nowblock->offsetX = 19;
		}
		drawboard();
		if (nowblock->offsetX > cols - 4)nowblock->offsetX = cols - 4;
		if (iscollide(nowblock))nowblock->stock(bakblock);
		
		updata = true;
		Sleep(50);
	}
	else if ( GetAsyncKeyState(VK_DOWN) & 0X8000) {
		bakblock = *nowblock;
		nowblock->drop();
		drawboard();
		if (iscollide(nowblock))nowblock->stock(bakblock);
		updata = true;
		Sleep(50);
	}
	else if (GetAsyncKeyState(VK_UP) & 0X8000){
		bakblock = *nowblock;
		nowblock->reverse();
		drawboard();
		if (iscollide(nowblock))nowblock->stock(bakblock);
		updata = true;
		Sleep(150);
	}
	
	
}
void Tetris::drawboard()
{
	setfillcolor(BLACK);
	fillrectangle(0, MENU_HEIGHT, 680, 500);
	dropblock();
	if (nowblock) nowblock->draw();
	drawnextblock();
	settextcolor(WHITE);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(500, 150, _T("数据结构"));
	line(500, 180, 620, 180);
	TCHAR scoretext[50], leveltext[50], linetext[50];
	swprintf_s(scoretext, _T("分数：%d"),score);
	swprintf_s(leveltext, _T("等级：%d"),level);
	swprintf_s(linetext, _T("消行数：%d"),linecount);
	outtextxy(500, 200, scoretext);
	outtextxy(500, 240, leveltext);
	outtextxy(500, 280, linetext);
	outtextxy(500, 350, _T("操作说明"));
	line(500, 380, 620, 380);
	outtextxy(500, 400, _T("方向键：移动/旋转"));
	outtextxy(500, 430,_T("空格：直接落地"));
	outtextxy(500,460, _T("ESC:退出游戏"));
	FlushBatchDraw();
}

int Tetris::getdelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount64(); // 修复：使用GetTickCount64防止溢出
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = static_cast<int>(currentTime - lastTime);
		lastTime = currentTime;
		return ret;
	}
	return 0;
}

void Tetris::lendclear()
{
	int linescleared = 0;
	for (int i = rows - 1; i >= 0; i--) {
		bool full = true;
		for (int j = 0; j <cols; j++) {
			if (map[i][j] == 0) {
				full = false;
				break;
			}
		}
		if (full) {
			linescleared++;
			linecount++;
			for (int k = i; k > 0; k--) {
				for (int j=0;j<cols;j++){
					map[k][j] = map[k - 1][j];
					colormap[k][j] = colormap[k - 1][j];
				}
					
			}
			for (int j=0;j<cols;j++){
				map[0][j] = 0;
				colormap[0][j] = BLACK;
			}
			i++;
		}
	}
	if (linescleared > 0) {
		int scoreadd[] = { 0,100,300,700,1500 };
		int index = linescleared < 5 ? linescleared : 4;
		score += scoreadd[index];
		updatalevelandspeed();
		updata = true;
	}

}
void Tetris::drawnextblock()
{
	if (nextblock == nullptr) return;
	int size = 20;
	settextcolor(WHITE);
	outtextxy(NEXT_X+50, NEXT_Y - 20, _T("NEXT"));
	setfillcolor(nextblock->blockcolor);
	for (int i = 0; i < 4; i++) {
		int a = nextblock->smallblock[i].x * size + NEXT_X-10;
		int b = nextblock->smallblock[i].y * size + NEXT_Y+10;
		setlinecolor(WHITE);
		fillrectangle(a, b, a + size - 1, b + size - 1);
		rectangle(a, b, a + size - 1, b + size - 1);
	}
}
bool Tetris::island(Block* block)
{
	return iscollide(block);
}

void Tetris::dropbottom()
{
	if (nowblock == nullptr) return;
	while (true) {
		bakblock = *nowblock;
		nowblock->drop();
		if (iscollide(nowblock)) {
			nowblock->stock(bakblock);
			break;
		}
	}
	saveblock(nowblock);
	lendclear();
	delete nowblock;
	nowblock = nextblock;
	nextblock = new Block();
	if (windowfull()) {
		cleardevice();
		drawmenu();
	}
	lendclear();
	updata = true;
}

bool Tetris::iscollide(Block* block)
{
	int size = blocksize;
	for (int i = 0; i < 4; i++) {
		int drawX = block->smallblock[i].x * size+50 + block->offsetX * size;
		int drawY = block->smallblock[i].y * size +50+ block->offsetY * size;
		int mapX = (drawX -50) / size;
		int mapY = (drawY -50) / size;
		if (mapX < 0 || mapX >= cols || mapY >= rows) {
			return true;
		}
		if (mapY < 0 || (mapY >= 0 && colormap[mapY][mapX] != BLACK)) {
			return true;
		}
	}
	return false;
}

void Tetris::updatalevelandspeed()
{
	if (linecount >= level * 10) {
		level++;
		delay = max(speed_normal - (level - 1) * 50, speed_fast);
	}
}

bool Tetris::windowfull()
{
	if (nowblock == nullptr) return false;
	int size = blocksize;
	for (int i = 0; i < 4; i++) {
		int drawX = nowblock->smallblock[i].x * size + 50 + nowblock->offsetX * size;
		int drawY = nowblock->smallblock[i].y * size + 50 + nowblock->offsetY * size;
		int mapX = (drawX-50) / size;
		int mapY = (drawY-50 ) / size;
		if (mapY < 0) {
			return true;
		}
		if (mapY >= 0 && mapY < rows && mapX >= 0 && mapX < cols) {
			if (map[mapY][mapX] == 1){
			     return true;
		    }
		}
	}
	return false;
}



void Tetris::drop() {
	bakblock = *nowblock;
	nowblock->drop();
	if (iscollide(nowblock)){
		nowblock->stock(bakblock);
		saveblock(nowblock);
		lendclear();
		delete nowblock;
		nowblock = nextblock;
		nextblock = new Block();
		if (windowfull()) {
			gameover = true;
			cleardevice();
			drawmenu();
			settextcolor(RED);
			settextstyle(36, 0, _T("宋体"));
			outtextxy(270, 200, _T("游戏失败"));
			TCHAR finalscore[50];
			swprintf_s(finalscore, _T("最终分数为：%d"), score);
			outtextxy(200, 250, finalscore);
			FlushBatchDraw();
			Sleep(1000);
			showrank();
			updata = true;
			cleardevice();
			exit(0);
		}
		lendclear();
		updata = true;
	}
}

void Tetris::saveblock(Block* block)
{
	int size = blocksize;
	for (int i = 0; i < 4; i++) {
		int drawX = block->smallblock[i].x * size +50+  block->offsetX * size;
		int drawY = block->smallblock[i].y * size +50+  block->offsetY * size;
		int mapX = (drawX-50 ) / size;
		int mapY = (drawY -50) / size;
		if (mapY < 0) {
			gameover = true;
			return;
		}
		if (mapY >= 0 && mapY < rows && mapX >= 0 && mapX < cols) {
			map[mapY][mapX] = 1;
			colormap[mapY][mapX] = block->blockcolor;
		}
	}
}



void Tetris::dropblock()
{
	int size = blocksize;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j]==1) {
				int x = j * size+50 ;
				int y = i * size +50;
				setfillcolor(colormap[i][j]);
				fillrectangle(x, y, x + size - 1, y + size - 1);
				setlinecolor(WHITE);
				rectangle(x, y, x + size - 1, y + size - 1);
			}
		}
	}
}

void Tetris::reverseblock()
{
	if (nowblock == nullptr) return;
	Point temp[4];
	for (int i = 0; i < 4; i++) {
		temp[i] = nowblock->smallblock[i];
	}
	nowblock->reverse();
	if (iscollide(nowblock)) {
		for (int i = 0; i < 4; i++) {
			nowblock->smallblock[i] = temp[i];
		}
	}
	updata = true;
}

void Tetris::handlemenu()
{
	if (MouseHit()) {
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.y <= MENU_HEIGHT) {
				int menuwidth = 680 / MENU_MAX;
				int menuindex = msg.x / menuwidth;
				if (gameover && menuindex != MENU_START && menuindex != MENU_RANK && menuindex != MENU_EXIT) {
					return;
				}
				switch (menuindex) {
				case MENU_START:
					if (gameover) {
						init();
						score = 0;
						linecount = 0;
						level = 1;
						gameover = false;
						started = false;
						for (int i = 0; i < rows; i++) {
							fill(map[i].begin(), map[i].end(), 0);
							fill(colormap[i].begin(), colormap[i].end(), BLACK);
						}
					}
					if (!started) {
						if (nowblock) delete nowblock;
						if (nextblock) delete nextblock;
						nowblock = new Block();
						nextblock = new Block();
						started = true;
					}
					paused = false;
					updata = true;
					break;
				case MENU_PAUSE:
					if (started && !gameover) {
						paused = !paused;
					}
					break;
				case MENU_RANK:
					showrank();
					break;
				case MENU_EXIT:
					closegraph();
					exit(0);
					break;
				}
				updata = true;
		   }
		}
	}
}

void Tetris::drawmenu()
{
	setfillcolor(RGB(60, 60, 60));
	fillrectangle(0, 0, 680, MENU_HEIGHT);
	int menuwidth = 680 / MENU_MAX;
	for (int i = 0; i < MENU_MAX; i++) {
		int x = i * menuwidth + menuwidth / 4;
		outtextxy(x, 5, menutexts[i]);
	}
}

void Tetris::pausegame()
{
	setfillcolor(RGB(0, 0, 180));
	fillrectangle(200, 200, 480, 300);
	settextcolor(WHITE);
	settextstyle(36, 0, _T("宋体"));
	outtextxy(270, 225, _T("游戏暂停"));
	FlushBatchDraw();
	while (true) {
		if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				break;
			}
		}
		if (_kbhit()) {
			int ch = _getch();
			if (ch == 32) {
				break;
			}
		}
	}

}

void Tetris::showrank() {
	ranklist.showrank();
	updata = true;
}

