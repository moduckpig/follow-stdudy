#include "Ranklist.h"
#include  <easyx.h>
#include <tchar.h>
#include "Tetris.h"

void Ranklist::loadfromfile()
{
	ifstream file(filename);
	if (!file) return;
	string name;
	int s;
	while (file >> name >> s) {
		interorupdata(name, s);
	}
	file.close();
}

void Ranklist::savetofile()
{
	ofstream file(filename);
	Ranknode* p = head->next;
	while (p) {
		file << p->username << " " << p->score << endl;
		p = p->next;
	}
	file.close();
}



Ranklist::Ranklist()
{
	head = new Ranknode("", 0);
	loadfromfile();
}

Ranklist::~Ranklist()
{
	savetofile();
	Ranknode* p = head;
	while (p) {
		Ranknode* q = p;
		p = p->next;
		delete q;
	}
}

void Ranklist::interorupdata(string name,int score)
{
	Ranknode* p = head->next;
	Ranknode* pre = head;
	while (p) {
		if (p->username == name) {
			if (score > p->score) {
				p->score = score;
			}
			savetofile();
			return;
		}
		pre = p;
		p = p->next;
	}
	p = head->next;
	pre = head;
	while (p && p->score > score) {
		pre = p;
		p = p->next;
	}
	Ranknode* newnode = new Ranknode(name, score);
	newnode->next = p;
	pre->next = newnode;
	savetofile();
}

void Ranklist::deleteuser(string name)
{
	Ranknode* p = head->next;
	Ranknode* pre = head;
	while (p) {
		if (p->username == name) {
			pre->next = p->next;
			delete p;
			savetofile();
			return;
		}
		pre = p;
		p = p->next;
	}
		MessageBox(NULL, _T("未找到该用户！"), _T("提示"), MB_OK);
}

void Ranklist::showrank()
{
	cleardevice();
	settextcolor(WHITE);
	setbkcolor(BLACK);
	cleardevice();
	settextstyle(36, 0, _T("黑体"));
	outtextxy(250, 50, _T("排行榜"));
	line(200, 100, 480, 100);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(220, 120, _T("排名"));
	outtextxy(280, 120, _T("用户"));
	outtextxy(400, 120, _T("分数"));
	line(200, 150, 480, 150);
	Ranknode* p = head->next;
	int rank = 1;
	int y = 180;
	int pre_score = -1;
	while (p && rank <= 10) {
		TCHAR ranktext[10], scoretext[20];
		if (p->score==pre_score){ }
		else {
			rank = y / 30 - 5;
			pre_score = p->score;
		}
		_itow_s(rank, ranktext, 10);
		_itow_s(p->score, scoretext, 10);
		outtextxy(230, y, ranktext);
		outtextxy(280, y, wstring(p->username.begin(), p->username.end()).c_str());
		outtextxy(420, y, scoretext);
		p = p->next;
		rank++;
		y += 30;
	}
	line(200, y + 20, 480, y + 20);
	outtextxy(220, y + 40, _T("点击左侧返回，右侧提交成绩"));
	setfillcolor(RGB(100, 100, 100));
	fillrectangle(220, y + 80, 300, y + 120);
	fillrectangle(380, y + 80, 460, y + 120);
	settextcolor(WHITE);
	outtextxy(235, y + 85, _T("返回"));
	outtextxy(395, y + 85, _T("提交"));
	FlushBatchDraw();
	while (true) {
		if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				if (msg.x >= 220 && msg.x <= 300 && msg.y >= y + 80 && msg.y <= y + 120) {
					break;
				}
				else if (msg.x >= 380 && msg.x <= 460 && msg.y >= y + 80 && msg.y < y + 120) {
					TCHAR username[50];
					if (InputBox(username, 50, _T("请输入用户名："), _T("提交成绩")) == IDOK) {
						string name;
						for (int i = 0; username[i] != '\0'; i++) {
							name += (char)username[i];
						}
						interorupdata(name, Tetris::getscore());
						MessageBox(NULL, _T("提交成绩成功！"), _T("提示"), MB_OK);
						showrank();
						break;
					}

				}
			}
		}
	}
}

