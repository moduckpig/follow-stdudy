#include <iostream>
#include <easyx.h>
#include <vector>
#include <ctime>
using namespace std;
class Sprite {
protected:
	int m_x;
	int m_y;
	COLORREF m_color;
public:
	Sprite() :Sprite(0, 0, YELLOW) {};
	Sprite(int x, int y, COLORREF mycolor = YELLOW) :m_x(x), m_y(y), m_color(mycolor) {};
	virtual void draw();
	void moveby(int x, int y);

};
class Snake :public Sprite {
private:
	vector<Sprite>nodes;
public:
	int dir;
	Snake() :Snake(0, 0) {}
	Snake(int x, int y) :Sprite(x, y), dir(VK_RIGHT) {
		nodes.push_back(Sprite(30, 10));
		nodes.push_back(Sprite(20, 10));
		nodes.push_back(Sprite(10, 10));
	}
	void bodyMove();//蛇的身体移动
	void increment();//蛇身增加
	int getLength();

};
class Food :public Sprite {
public:
	Food() :Sprite(0, 0, YELLOW){
		changeFoodpPos();
	}
	void draw()override;
	
};
class Wall :public Sprite{
public:
	wall() :Sprite(0, 0, LIGHTGRAY) {}
	void setWall();
};
class GameSence {
private :
	Snake snake;
	Food food;
	Wall wall;
public:

};
void moveby(int x, int y) {
	m_x += x;
	m_y += y;
}
void setWall() {}
void bodyMove() {
	for (size_t i = nodes.size() - 1; i > 0; i--) {
		nodes[i] = nodes[i - 1];
		
	}
}