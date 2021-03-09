#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "game.h"

Game::Game()
{
	playerTexture = LoadImage("player.bmp");
	activistTexture = LoadImage("activist.bmp");
	enemyTexture = LoadImage("enemy.bmp");
	farmTexture = LoadImage("farm.bmp");

	animalsSaved = 0;
	animalsKilled = 0;
	frame = 0;
	spawnNPC();
}

void Game::run()
{
	int fps = 60;
	Uint32 frameStart;
	int frameTime;
	int frameDelay = 1000 / fps;
	int i = 0;

	while (isRunning())
	{
		frameStart = SDL_GetTicks();

		// ACTIVIST AND ENEMY MOVEMENT
		if (i == 3)
		{
			activistMovement();
			enemyMovement();
			i = 0;
		}
		else i++;

		// COLLISION
		collision();

		// DISPLAY
		clearScreen();
		displayFarms(renderer);
		displayActivists(renderer);
		displayEnemies(renderer);
		displayPlayer(renderer);
		displayScreen();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}
}

bool Game::isRunning()
{
	if (!(std::all_of(animalsInFarm.begin(), animalsInFarm.end(), [](int a) {return a > 0; })))
	{
		if (animalsSaved > animalsKilled)
		{
			std::cout << "You won.\nYou saved more animals than were killed.\n";
			return false;
		}
		else { std::cout << "You lost.\nEnemies killed more animals than you saved.\n"; return false; }
	}
	else if (animalsSaved == 25) { std::cout << "You won.\nYou saved all animals.\n"; return false; }
	else if (animalsKilled == 25) { std::cout << "You lost.\nEnemies killed all animals.\n"; return false; }
	else if(enemyRect.size() == 0) { std::cout << "You won.\nYou killed all enemies.\n"; return false; }

	return handleEvents();
}

bool Game::handleEvents()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) running = false;
		else playerMovement();
	}
	return running;
}

void Game::spawnNPC()
{
	SDL_Rect tmpRect{ 0,0,25,50 };
	std::vector<int> tmpVect;
	tmpVect.push_back(0);
	tmpVect.push_back(0);
	for (int i = 0; i < 5; i++)
	{
		bool overlaps = true;
		while (overlaps)
		{
			overlaps = false;
			tmpRect.x = rand() % (1280 - tmpRect.w + 1);
			tmpRect.y = rand() % (720 - tmpRect.h + 1);
			for (int j = 0; j < farmRect.size() && overlaps == false; ++j)
				overlaps = rectOverlap(farmRect[i], tmpRect);
		}
		activistRect.push_back(tmpRect);
		activistDirCnt.push_back(0);
		activistDir.push_back(0);
		
		overlaps = true;
		while (overlaps)
		{
			overlaps = false;
			tmpRect.x = rand() % (1280 - tmpRect.w + 1);
			tmpRect.y = rand() % (720 - tmpRect.h + 1);
			for (int j = 0; j < farmRect.size() && overlaps == false; ++j)
				overlaps = rectOverlap(farmRect[i], tmpRect);
		}
		enemyRect.push_back(tmpRect);
		enemyDirCnt.push_back(0);
		enemyDir.push_back(0);

		activistMoveTo.push_back(tmpVect);
		enemyMoveTo.push_back(tmpVect);
	}
}

void Game::playerMovement()
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			if (canMove(playerRect, 3, 5)) playerRect.x -= 5;
			break;
		case SDLK_d:
			if (canMove(playerRect, 4, 5)) playerRect.x += 5;
			break;
		case SDLK_w:
			if (canMove(playerRect, 1, 5)) playerRect.y -= 5;
			break;
		case SDLK_s:
			if (canMove(playerRect, 2, 5)) playerRect.y += 5;
		}
	}
}

void Game::activistMovement()
{
	for(int i = 0; i < activistRect.size(); ++i)
	{
		if (findTarget(false, i, activistRect[i]))
		{
			if (activistMoveTo[i][0] - activistRect[i].x > 0 && canMove(activistRect[i], 4, 1)) activistRect[i].x++;
			else if (activistMoveTo[i][0] - activistRect[i].x < 0 && canMove(activistRect[i], 3, 1)) activistRect[i].x--;

			if (activistMoveTo[i][1] - activistRect[i].y > 0 && canMove(activistRect[i], 2, 1)) activistRect[i].y++;
			else if (activistMoveTo[i][1] - activistRect[i].y < 0 && canMove(activistRect[i], 1, 1)) activistRect[i].y--;
		}
		else
		{
			activistMoveTo[i][0] = 0;
			activistMoveTo[i][1] = 0;
			if (activistDir[i] == 0 || activistDirCnt[i] == 30)
			{
				activistDir[i] = rand() % (5 - 1) + 1;
				activistDirCnt[i] = 0;
			}
			if (canMove(activistRect[i], activistDir[i], 1))
			{
				switch (activistDir[i])
				{
				case 1: // up
					activistRect[i].y--;
					activistDirCnt[i]++;
					break;
				case 2: // down
					activistRect[i].y++;
					activistDirCnt[i]++;
					break;
				case 3: // left
					activistRect[i].x--;
					activistDirCnt[i]++;
					break;
				case 4: // right
					activistRect[i].x++;
					activistDirCnt[i]++;
				}
			}
			else activistDir[i] = 0; // can't move in this way, so reset
		}
	}
}

void Game::enemyMovement()
{
	for (int i = 0; i < enemyRect.size(); ++i)
	{
		if (findTarget(true, i, enemyRect[i]))
		{
			if (enemyMoveTo[i][0] - enemyRect[i].x > 0 && canMove(enemyRect[i], 4, 1)) enemyRect[i].x++;
			else if (enemyMoveTo[i][0] - enemyRect[i].x < 0 && canMove(enemyRect[i], 3, 1)) enemyRect[i].x--;

			if (enemyMoveTo[i][1] - enemyRect[i].y > 0 && canMove(enemyRect[i], 2, 1)) enemyRect[i].y++;
			else if (enemyMoveTo[i][1] - enemyRect[i].y < 0 && canMove(enemyRect[i], 1, 1)) enemyRect[i].y--;
		}
		else
		{
			enemyMoveTo[i][0] = 0;
			enemyMoveTo[i][1] = 0;
			if (enemyDir[i] == 0 || enemyDirCnt[i] == 30)
			{
				enemyDir[i] = rand() % (5 - 1) + 1;
				enemyDirCnt[i] = 0;
			}
			if (canMove(enemyRect[i], enemyDir[i], 1))
			{
				switch (enemyDir[i])
				{
				case 1: // up
					enemyRect[i].y--;
					enemyDirCnt[i]++;
					break;
				case 2: // down
					enemyRect[i].y++;
					enemyDirCnt[i]++;
					break;
				case 3: // left
					enemyRect[i].x--;
					enemyDirCnt[i]++;
					break;
				case 4: // right
					enemyRect[i].x++;
					enemyDirCnt[i]++;
				}
			}
			else enemyDir[i] = 0; // can't move in this way, so reset
		}
	}
}

bool Game::canMove(SDL_Rect &rect, int where, int moveBy)
{
	int xy[2] = { 0,0 };
	switch (where)
	{
	case 1: // up
		xy[1] = -moveBy;
		return((rect.y - moveBy >= 0) && collisionWithFarm(rect, xy));
		break;
	case 2: // down
		xy[1] = moveBy;
		return((rect.y + rect.h + moveBy <= 720) && collisionWithFarm(rect, xy));
		break;
	case 3: // left
		xy[0] = -moveBy;
		return((rect.x - moveBy >= 0) && collisionWithFarm(rect, xy));
		break;
	case 4: // right
		xy[0] = moveBy;
		return((rect.x + rect.w + moveBy <= 1280) && collisionWithFarm(rect, xy));
	}
}

void Game::collision()
{
	frame++;
	SDL_Rect tmpRect;
// player collision
	// with farms
	for (int i = 0; i < farmRect.size(); ++i)
	{
		tmpRect = {farmRect[i].x - 5, farmRect[i].y - 5, 210, 110};
		if (rectOverlap(playerRect, tmpRect) && frame == 60)
		{
			animalsInFarm[i]--;
			if (animalsInFarm[i] == 0) deleteFarm(i);
			animalsSaved++;
		}
	}
	// with enemies
	std::vector<int> indexToDelete;
	for (int i = 0; i < enemyRect.size(); ++i)
	{
		if (rectOverlap(playerRect, enemyRect[i]))
		{
			indexToDelete.push_back(i);
			if (indexToDelete.size() > 1) { running = false; std::cout << "GAME OVER --- TOO MANY ENEMIES\n"; return; }
		}
	}
	for (int i = 0; i < indexToDelete.size(); ++i)
		deleteEnemyVectorEl(indexToDelete[i]);
// activist enemy collision
	// between themselves
	indexToDelete.clear();
	for (int i = 0; i < enemyRect.size(); ++i)
		for (int j = 0; j < activistRect.size(); ++j)
			if (rectOverlap(activistRect[j], enemyRect[i])) indexToDelete.push_back(i);
	for (int i = 0; i < indexToDelete.size(); ++i)
		deleteEnemyVectorEl(indexToDelete[i]);
	// with farms
	for (int i = 0; i < farmRect.size(); ++i)
	{
		tmpRect = {farmRect[i].x - 1, farmRect[i].y - 1, 202, 102};
		for (int j = 0; j < enemyRect.size(); ++j)
			if (rectOverlap(enemyRect[j], tmpRect) && frame == 60)
			{
				animalsInFarm[i]--;
				if (animalsInFarm[i] == 0) deleteFarm(i);
				animalsKilled++;
			}
	}
	for (int i = 0; i < farmRect.size(); ++i)
	{
		tmpRect = {farmRect[i].x - 1, farmRect[i].y - 1, 202, 102};
		for (int j = 0; j < activistRect.size(); ++j)
			if (rectOverlap(activistRect[j], tmpRect) && frame == 60)
			{
				animalsInFarm[i]--;
				if (animalsInFarm[i] == 0) deleteFarm(i);
				animalsSaved++;
			}
	}

	if (frame == 60) frame = 0;
}

bool Game::collisionWithFarm(SDL_Rect rect, int xy[])
{
	rect.x += xy[0];
	rect.y += xy[1];
	for (int i = 0; i < farmRect.size(); i++)
		if (rectOverlap(rect, farmRect[i])) return false;
	return true;
}

bool Game::findTarget(bool act_or_enemy, int index, SDL_Rect &rect)
{
	SDL_Rect maskRect = {rect.x - rect.w, rect.y - rect.h, 150, 300};
	if (act_or_enemy) // find player or activists
	{
		if (rectOverlap(maskRect, playerRect))
		{
			enemyMoveTo[index][0] = playerRect.x;
			enemyMoveTo[index][1] = playerRect.y;
			return true;
		}
		for (int i = 0; i < activistRect.size(); i++)
			if (rectOverlap(maskRect, activistRect[i]))
			{
				enemyMoveTo[index][0] = activistRect[i].x;
				enemyMoveTo[index][1] = activistRect[i].y;
				return true;
			}
	}
	else // find enemies
		for (int i = 0; i < enemyRect.size(); i++)
			if (rectOverlap(maskRect, enemyRect[i]))
			{
				activistMoveTo[index][0] = enemyRect[i].x;
				activistMoveTo[index][1] = enemyRect[i].y;
				return true;
			}
	for(int i = 0; i < farmRect.size(); ++i) // find farms
		if (rectOverlap(maskRect, farmRect[i]))
		{
			if (act_or_enemy)
			{
				enemyMoveTo[index][0] = farmRect[i].x;
				enemyMoveTo[index][1] = farmRect[i].y;
			}
			else
			{
				activistMoveTo[index][0] = farmRect[i].x;
				activistMoveTo[index][1] = farmRect[i].y;
			}
			return true;
		}
	return false;
}