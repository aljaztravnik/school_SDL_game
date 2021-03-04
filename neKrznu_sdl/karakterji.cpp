#include <iostream>
#include <string>
#include <cmath>
#include "karakterji.h"

Game::Game()
{
	playerTexture = LoadImage("player.bmp");
	activistTexture = LoadImage("activist.bmp");
	enemyTexture = LoadImage("enemy.bmp");
	farmTexture = LoadImage("farm.bmp");
	arial = TTF_OpenFont("arial.ttf", 14);
	white = {255,255,255,255};

	maskRect = {0,0,150, 300};
	playerRect = {0,0,50,100};

	bool nakljucno = true;
	std::cout << "Ali zelite zaceti na nakljucni poziciji [0, 1]: ";
	std::cin >> nakljucno;
	std::cin.ignore();
	if (nakljucno)
	{
		playerRect.x = rand() % 1231;
		playerRect.y = rand() % 621;
	}
	else
	{
		std::cout << "Vpisite x pozicijo igralca: ";
		std::cin >> playerRect.x;
		std::cout << "Vpisite y pozicijo igralca: ";
		std::cin >> playerRect.y;
	}
	SDL_Rect tempRect{ 0,0,25,50 };
	SDL_Rect tmpRect2{ 0,0,200,100 };
	for (int i = 0; i < 5; ++i)
	{
		tempRect.x = rand() % (1280 - tempRect.w + 1);
		tempRect.y = rand() % (720 - tempRect.h + 1);
		activistRect.push_back(tempRect);
		activistDirCnt.push_back(0);
		activistDir.push_back(0);

		tempRect.x = rand() % (1280 - tempRect.w + 1);
		tempRect.y = rand() % (720 - tempRect.h + 1);
		enemyRect.push_back(tempRect);
		enemyDirCnt.push_back(0);
		enemyDir.push_back(0);

		tmpRect2.x = rand() % (1280 - tmpRect2.w + 1);
		tmpRect2.y = rand() % (720 - tmpRect2.h + 1);
		farmRect.push_back(tmpRect2);
		animalsInFarm.push_back(5);
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
		int xy[] = { 0,0 };
		if (findTarget(false, xy, activistRect[i]))
		{
			if (xy[0] - activistRect[i].x > 0) activistRect[i].x++;
			else if (xy[0] - activistRect[i].x < 0) activistRect[i].x--;

			if (xy[1] - activistRect[i].y > 0) activistRect[i].y++;
			else if (xy[1] - activistRect[i].y < 0) activistRect[i].y--;
		}
		else
		{
			if (activistDir[i] == 0 || activistDirCnt[i] == 10)
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
		int xy[] = { 0,0 };
		if (findTarget(false, xy, enemyRect[i]))
		{
			if (xy[0] - enemyRect[i].x > 0) enemyRect[i].x++;
			else if (xy[0] - enemyRect[i].x < 0) enemyRect[i].x--;

			if (xy[1] - enemyRect[i].y > 0) enemyRect[i].y++;
			else if (xy[1] - enemyRect[i].y < 0) enemyRect[i].y--;
		}
		else
		{
			if (enemyDir[i] == 0 || enemyDirCnt[i] == 10)
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
	bool yes = false;
	switch (where)
	{
	case 1: // up
		if (rect.y - moveBy >= 0) yes = true;
		break;
	case 2: // down
		if (rect.y + rect.h + moveBy <= 720) yes = true;
		break;
	case 3: // left
		if (rect.x - moveBy >= 0) yes = true;
		break;
	case 4: // right
		if (rect.x + rect.w + moveBy <= 1280) yes = true;
	}
	return yes;
}

bool Game::valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool Game::rectOverlap(SDL_Rect &A, SDL_Rect &B)
{
	bool xOverlap = valueInRange(A.x, B.x, B.x + B.w) ||
		valueInRange(B.x, A.x, A.x + A.w);

	bool yOverlap = valueInRange(A.y, B.y, B.y + B.h) ||
		valueInRange(B.y, A.y, A.y + A.h);

	return xOverlap && yOverlap;
}

void Game::collision()
{
// player collision
	// with farms
	for (int i = 0; i < farmRect.size(); ++i)
		if (rectOverlap(playerRect, farmRect[i])) animalsInFarm[i]--;
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
		enemyRect.erase(enemyRect.begin() + indexToDelete[i]);
// activist enemy collision
	// between themselves
	indexToDelete.clear();
	for (int i = 0; i < enemyRect.size(); ++i)
		for (int j = 0; j < activistRect.size(); ++j)
			if (rectOverlap(activistRect[j], enemyRect[i])) indexToDelete.push_back(i);
	for (int i = 0; i < indexToDelete.size(); ++i)
		enemyRect.erase(enemyRect.begin() + indexToDelete[i]);
	// with farms
	for (int i = 0; i < farmRect.size(); ++i)
		for(int j = 0; j < enemyRect.size(); ++j)
			if (rectOverlap(enemyRect[j], farmRect[i])) animalsInFarm[i]--;
	for (int i = 0; i < farmRect.size(); ++i)
		for (int j = 0; j < activistRect.size(); ++j)
			if (rectOverlap(activistRect[j], farmRect[i])) animalsInFarm[i]--;
}

bool Game::findTarget(bool act_or_enemy, int xy[], SDL_Rect &rect)
{
	SDL_Rect maskRect = {rect.x - rect.w, rect.y - rect.h, 150, 300};
	if (act_or_enemy) // find activists
		for (int i = 0; i < activistRect.size(); i++)
			if (rectOverlap(maskRect, activistRect[i]))
			{
				xy[0] = activistRect[i].x;
				xy[1] = activistRect[i].y;
				return true;
			}
	else // find enemies
		for (int i = 0; i < enemyRect.size(); i++)
			if (rectOverlap(maskRect, enemyRect[i]))
			{
				xy[0] = enemyRect[i].x;
				xy[1] = enemyRect[i].y;
				return true;
			}
	for(int i = 0; i < farmRect.size(); ++i) // find farms
		if (rectOverlap(maskRect, farmRect[i]))
		{
			xy[0] = farmRect[i].x;
			xy[1] = farmRect[i].y;
			return true;
		}
	return false;
}

void Game::displayPlayer()
{
	/*maskRect.x = playerRect.x - playerRect.w;
	maskRect.y = playerRect.y - playerRect.h;
	SDL_RenderSetClipRect(renderer, &maskRect);*/
	SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
}

void Game::displayActivists_Enemies()
{
	for (int i = 0; i < activistRect.size(); ++i)
		SDL_RenderCopy(renderer, activistTexture, nullptr, &activistRect[i]);
	for (int i = 0; i < enemyRect.size(); ++i)
		SDL_RenderCopy(renderer, enemyTexture, nullptr, &enemyRect[i]);
}

void Game::displayFarms()
{
	SDL_Surface* messageSurface;
	SDL_Texture* messageTexture;
	SDL_Rect messageRect{ 0,0,50,50 };
	for (int i = 0; i < farmRect.size(); ++i)
	{
		messageSurface = TTF_RenderText_Solid(arial, (std::to_string(animalsInFarm[i])).c_str(), white);
		messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
		messageRect.x = farmRect[i].x + (farmRect[i].w / 2) - (messageRect.w / 2);
		messageRect.y = farmRect[i].y + (farmRect[i].h / 2) + (messageRect.h / 8);

		SDL_RenderCopy(renderer, farmTexture, nullptr, &farmRect[i]);
		SDL_RenderCopy(renderer, messageTexture, nullptr, &messageRect);

		SDL_FreeSurface(messageSurface);
		SDL_DestroyTexture(messageTexture);
	}
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

void Game::destroyCharactersSDL()
{
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(activistTexture);
	SDL_DestroyTexture(enemyTexture);
}