#include <iostream>
#include "player.h"

Player::Player()
{
	maskRect = { 0,0,450,500 };
	playerRect = { 0,0,50,100 };

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

Player::~Player()
{
	SDL_DestroyTexture(playerTexture);
}

void Player::displayPlayer(SDL_Renderer* &renderer)
{
	/*maskRect.x = playerRect.x - 200; ////////////////////////////////////// UNCOMMENT TO ADD PLAYER MASK
	maskRect.y = playerRect.y - 200;
	SDL_RenderSetClipRect(renderer, &maskRect);*/
	SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
}