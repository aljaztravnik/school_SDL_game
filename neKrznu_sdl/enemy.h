#pragma once
#include <vector>
#include <SDL.h>

class Enemy
{
protected:
	std::vector<SDL_Rect> enemyRect;
	std::vector<int> enemyDir;
	std::vector<int> enemyDirCnt;
	std::vector<std::vector<int>> enemyMoveTo;
	SDL_Texture* enemyTexture;
public:
	~Enemy();
	void deleteEnemyVectorEl(int);
	void displayEnemies(SDL_Renderer* &);
};