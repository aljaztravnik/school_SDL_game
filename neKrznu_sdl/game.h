#pragma once
#include "handlingGameStuff.h"
#include "player.h"
#include "activist.h"
#include "enemy.h"
#include "farm.h"
#include "commonFunctions.h"

class Game : public GameStuff, public Player, public Activist, public Enemy, public Farm, public CommonFunctions
{
private:
	int animalsSaved;
	int animalsKilled;
	int frame;
public:
	Game();
	void run();
	bool isRunning();
	bool handleEvents();
	void spawnNPC();
	void playerMovement();
	void activistMovement();
	void enemyMovement();
	bool canMove(SDL_Rect &, int, int);
	void collision();
	bool collisionWithFarm(SDL_Rect, int[]);
	bool findTarget(bool, int, SDL_Rect &);
};