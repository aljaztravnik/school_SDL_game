#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "handlingGameStuff.h"

GameStuff::GameStuff()
{
	running = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) std::cout << "Failed to initialize SDL.\n" << "SDL ERROR: " << SDL_GetError() << '\n';
	window = SDL_CreateWindow("Ne krznu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL) std::cout << "Window creation error: " << SDL_GetError() << '\n';
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (TTF_Init() == -1) std::cout << "Failed to initialize SDL_ttf.\n";
}

SDL_Texture* GameStuff::LoadImage(std::string file)
{
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;
	loadedImage = SDL_LoadBMP(file.c_str());

	if (loadedImage != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		std::cout << SDL_GetError() << std::endl;
	return texture;
}

void GameStuff::clearScreen()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void GameStuff::displayScreen()
{
	SDL_RenderPresent(renderer);
}

void GameStuff::destroyGameSDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}