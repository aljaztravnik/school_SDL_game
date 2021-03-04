#pragma once
#include <SDL.h>

class GameStuff
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	SDL_Texture* maskTexture;
	SDL_Rect maskRect;
	bool running;
public:
	GameStuff();
	SDL_Texture* LoadImage(std::string);
	void clearScreen();
	void displayScreen();
	void destroySDL();
	void displayPlayer(SDL_Texture*, SDL_Rect*);
	void displayActivists_Enemies(SDL_Texture*, SDL_Rect*);
	SDL_Renderer* getRenderer();
	SDL_Event* getEvent();
};