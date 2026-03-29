#pragma once
#include <graphics.h>
struct Point {
	int x;
	int y;

};
class Block
{
public:
	Block();
	void type();
	bool drop();
	void reverse();
	void draw();
	bool island();
	void stock(const Block&backupblock);
	

public:
	Point smallblock[4];
	COLORREF blockcolor;
	int offsetY;
	int offsetX;
private:
	int blockType;
private:
	static COLORREF colors[7];
	static int size;
};

