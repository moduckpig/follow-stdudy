#include "Tetris.h"
#include "Block.h"

int main(void) {

	Tetris game(20,0,100,22,20);
	game.init();
	game.startplay();
	Block block;
	block.draw();
	system("pause");
	closegraph();
	return 0;
}