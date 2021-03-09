#include <iostream>
#include "enemy.h"

Enemy::~Enemy()
{
	SDL_DestroyTexture(enemyTexture);
}

void Enemy::deleteEnemyVectorEl(int i)
{
	enemyRect.erase(enemyRect.begin() + i);
	enemyMoveTo.erase(enemyMoveTo.begin() + i);
	enemyDir.erase(enemyDir.begin() + i);
	enemyDirCnt.erase(enemyDirCnt.begin() + i);
}

void Enemy::displayEnemies(SDL_Renderer* &renderer)
{
	for (int i = 0; i < enemyRect.size(); ++i)
		SDL_RenderCopy(renderer, enemyTexture, nullptr, &enemyRect[i]);
}