#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "karakterji.h"

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));

	Game game;
	int fps = 60;
	Uint32 frameStart;
	int frameTime;
	int frameDelay = 1000 / fps;
	
	while (game.handleEvents())
	{
		frameStart = SDL_GetTicks();

		/////// MOVEMENT AKTIVISTOV IN ENEMYEV
		game.activistMovement();
		game.enemyMovement();

		/////// DISPLAY STUFF
		game.clearScreen();
		game.displayActivists_Enemies();
		game.displayFarms();
		game.displayPlayer();
		game.displayScreen();

		game.collision();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}
	game.destroyCharactersSDL();
	game.destroyGameSDL();
	return 0;
}