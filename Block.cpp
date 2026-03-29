#include "Block.h"
#include <tchar.h>
#include <ctime>
#define ORANGE RGB(255, 165, 0)
#define PURPLE RGB(128, 0, 128)
int Block::size = 20;
COLORREF Block::colors[7] = { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE };
Block::Block()
{
	static bool seeded = false;
	if (!seeded) {
		srand(static_cast<unsigned int>(time(NULL)));
		seeded = true;
	}
    type();
}


void Block::type()
{
	offsetX = 13;
	offsetY = 0;
	int block[7][4] = {
		1,3,5,7,
		2,4,5,7,
		3,5,4,6,
		3,5,4,7,
		2,3,5,7,
		3,5,7,6,
		2,3,4,5
	};
	blockType = rand() % 7;

	for (int i = 0; i < 4; ++i) {
		int value = block[blockType][i];
		smallblock[i].y = value / 2;
		smallblock[i].x = value % 2 + 4;
	}
	blockcolor = colors[blockType];
}

bool Block::drop()
{
	offsetY += 1;
	return island();
}



void Block::reverse()
{
	Point p = smallblock[1];
	if (blockType==6) return;
	for (int i = 0; i < 4; i++) {
		Point tempt = smallblock[i];
		smallblock[i].x = p.x - tempt.y + p.y;
		smallblock[i].y = p.y + tempt.x - p.x;
	}
}



void Block::draw()
{
	for (int i = 0; i < 4; i++) {
		int a = smallblock[i].x * size +50+ offsetX * size;
		int b = smallblock[i].y * size+40+offsetY*size;
			setfillcolor(blockcolor);
			fillrectangle(a, b, a + size, b + size);
			setlinecolor(WHITE);
			rectangle(a, b, a + size, b + size);
	}
}

bool Block::island()
{
	int gridrows = 20;
	for (int i = 0; i < 4; i++) {
		if (smallblock[i].y + offsetY >= gridrows-1) {
			return true;
		}
	}
	return false;
}

void Block::stock(const Block& backupblock)
{
	this->offsetX = backupblock.offsetX;
	this->offsetY = backupblock.offsetY;
	for (int i = 0; i < 4; i++) {
		this->blockType = backupblock.blockType;
		this->blockcolor = backupblock.blockcolor;
	}
	for (int i = 0; i < 4; i++) {
		this->smallblock[i]=backupblock.smallblock[i];
	}
}

