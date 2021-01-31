#pragma once
#include <iostream>
#include <SDL.h>

class Player
{
private:
	SDL_Rect playerRect;
	SDL_Texture* playerTexture;
public:
	Player();
	void movement(SDL_Event);
	SDL_Texture* getPlayerTexture();
	void setPlayerTexture(SDL_Texture*);
	SDL_Rect getPlayerRect();
	void destroySDL();
};

class Activist
{
private:
	SDL_Rect activistRect;
	SDL_Texture* activistTexture;
public:
	Activist();
	void movement();
	void setActivistTexture(SDL_Texture*);
	SDL_Texture* getActivistTexture();
	SDL_Rect getActivistRect();
	void destroySDL();
};