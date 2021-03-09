#pragma once
#include <SDL.h>

class Player
{
protected:
	SDL_Rect playerRect;
	SDL_Rect maskRect;
	SDL_Texture* playerTexture;
public:
	Player();
	~Player();
	void displayPlayer(SDL_Renderer* &);
};