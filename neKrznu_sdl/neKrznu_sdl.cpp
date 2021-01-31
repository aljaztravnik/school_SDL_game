#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "handlingGameStuff.h"
#include "karakterji.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));

	GameStuff game;
	Player player;
	Activist activist;

	player.setPlayerTexture(game.LoadImage("player.bmp"));
	activist.setActivistTexture(game.LoadImage("activist.bmp"));
	
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&game.getEvent()))
		{
			if (game.getEvent().type == SDL_QUIT) running = false;
			else player.movement(game.getEvent());
		}
		game.clearScreen();
		game.displayPlayer(player.getPlayerTexture(), &(player.getPlayerRect()));
		game.displayActivist(activist.getActivistTexture(), &(activist.getActivistRect()));
		game.displayScreen();
	}

	player.destroySDL();
	activist.destroySDL();
	game.destroySDL();

	return 0;
}