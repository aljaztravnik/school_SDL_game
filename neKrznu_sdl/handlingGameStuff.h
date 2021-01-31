#pragma once
#include <iostream>
#include <SDL.h>

class GameStuff
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	bool running;
public:
	GameStuff();
	SDL_Texture* LoadImage(std::string);
	void clearScreen();
	void displayScreen();
	void destroySDL();
	void displayPlayer(SDL_Texture*, SDL_Rect*);
	void displayActivist(SDL_Texture*, SDL_Rect*);
	SDL_Renderer* getRenderer();
	SDL_Event getEvent();
};