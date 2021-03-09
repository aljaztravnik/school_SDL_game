#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));
	Game game;
	game.run();
	return 0;
}