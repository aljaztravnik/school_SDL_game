#pragma once
#include "handlingGameStuff.h"

class Game : public GameStuff
{
private:
	SDL_Rect playerRect;
	SDL_Rect maskRect;
	SDL_Texture* playerTexture;
	SDL_Texture* activistTexture;
	SDL_Texture* enemyTexture;
	SDL_Texture* farmTexture;
	std::vector<SDL_Rect> activistRect;
	std::vector<SDL_Rect> enemyRect;
	std::vector<SDL_Rect> farmRect;
	std::vector<int> activistDirCnt;
	std::vector<int> enemyDirCnt;
	std::vector<int> activistDir;
	std::vector<int> enemyDir;
	std::vector<int> animalsInFarm;

	TTF_Font* arial;
	SDL_Color white;
	SDL_Surface* numOfAnimals;
public:
	Game();
	void playerMovement();
	void activistMovement();
	void enemyMovement();
	bool canMove(SDL_Rect &, int, int);
	bool valueInRange(int, int, int);
	bool rectOverlap(SDL_Rect &, SDL_Rect &);
	void collision();
	bool findTarget(bool, int[], SDL_Rect &);
	void displayPlayer();
	void displayActivists_Enemies();
	void displayFarms();
	bool handleEvents();
	void destroyCharactersSDL();
};