#include "../includes/core.h"

int main(int argc, char *argv[]){
	Core* core = new Core( 25, 25 * 5);
	core->startGame();
	return 0;
}