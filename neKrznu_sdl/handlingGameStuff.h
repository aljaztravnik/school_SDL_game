#pragma once
#include <vector>
#include <SDL.h>
#include "SDL_ttf.h"

class GameStuff
{
protected:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	bool running;
public:
	GameStuff();
	~GameStuff();
	SDL_Texture* LoadImage(std::string);
	void clearScreen();
	void displayScreen();
};