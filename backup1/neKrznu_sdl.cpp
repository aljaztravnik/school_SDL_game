#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SDL.h>
#include "handlingGameStuff.h"
#include "karakterji.h"

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));

	GameStuff game;
	Player player;
	std::vector<Activist> activists(5);
	std::vector<Enemy> enemies(5);

	player.setPlayerTexture(game.LoadImage("player.bmp"));
	for (int i = 0; i < enemies.size(); ++i)
		enemies[i].setEnemyTexture(game.LoadImage("enemy.bmp"));
	for (int i = 0; i < enemies.size(); ++i)
		activists[i].setActivistTexture(game.LoadImage("activist.bmp"));

	
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(game.getEvent()))
		{
			if (game.getEvent()->type == SDL_QUIT) running = false;
			else player.movement(game.getEvent());
		}
		/////// MOVEMENT


		/////// DISPLAY STUFF
		game.clearScreen();
		for(int i = 0; i < activists.size(); ++i)
			game.displayActivists_Enemies(activists[i].getActivistTexture(), &(activists[i].getActivistRect()));
		for (int i = 0; i < enemies.size(); ++i)
			game.displayActivists_Enemies(enemies[i].getEnemyTexture(), &(enemies[i].getEnemyRect()));
		game.displayPlayer(player.getPlayerTexture(), &(player.getPlayerRect()));
		game.displayScreen();
	}

	player.destroySDL();
	for (int i = 0; i < activists.size(); ++i)
		activists[i].destroySDL();
	for (int i = 0; i < enemies.size(); ++i)
		enemies[i].destroySDL();
	game.destroySDL();

	return 0;
}