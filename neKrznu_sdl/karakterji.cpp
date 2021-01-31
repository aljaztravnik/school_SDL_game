#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "karakterji.h"

Player::Player()
{
	playerRect.w = 50;
	playerRect.h = 100;

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
}

void Player::setPlayerTexture(SDL_Texture* sentTexture)
{
	playerTexture = sentTexture;
}

void Player::movement(SDL_Event sentEvent)
{
	if (sentEvent.type == SDL_KEYDOWN)
	{
		switch (sentEvent.key.keysym.sym)
		{
			case SDLK_a:
				playerRect.x -= 5;
				break;
			case SDLK_d:
				playerRect.x += 5;
				break;
			case SDLK_w:
				playerRect.y -= 5;
				break;
			case SDLK_s:
				playerRect.y += 5;
		}
	}
}

SDL_Texture* Player::getPlayerTexture()
{
	return playerTexture;
}

SDL_Rect Player::getPlayerRect()
{
	return playerRect;
}

void Player::destroySDL()
{
	SDL_DestroyTexture(playerTexture);
}

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

Activist::Activist()
{
	activistRect.w = 25;
	activistRect.h = 50;
	activistRect.x = rand() % 1256;
	activistRect.y = rand() % 671;
}

void Activist::movement()
{
	// todo: nared random movement aktivista
}

SDL_Texture* Activist::getActivistTexture()
{
	return activistTexture;
}

SDL_Rect Activist::getActivistRect()
{
	return activistRect;
}

void Activist::setActivistTexture(SDL_Texture* sentTexture)
{
	activistTexture = sentTexture;
}

void Activist::destroySDL()
{
	SDL_DestroyTexture(activistTexture);
}