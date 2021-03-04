#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "handlingGameStuff.h"

GameStuff::GameStuff()
{
	running = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) std::cout << "SDL is shit\n" << "SDL ERROR: " << SDL_GetError() << '\n';
	window = SDL_CreateWindow("Ne krznu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL)
		std::cout << "Window creation error: " << SDL_GetError() << '\n';
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	maskTexture = LoadImage("maska.bmp");
	maskRect.w = 2560;
	maskRect.h = 1440;
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

SDL_Renderer* GameStuff::getRenderer()
{
	return renderer;
}

SDL_Event* GameStuff::getEvent()
{
	return &event;
}

void GameStuff::clearScreen()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void GameStuff::displayPlayer(SDL_Texture* playerTexture, SDL_Rect* playerRect)
{
	/*maskRect.x = playerRect->x - (maskRect.w / 2) + (playerRect->w / 2);
	maskRect.y = playerRect->y - (maskRect.h / 2) + (playerRect->h / 2);

	SDL_RenderCopy(renderer, maskTexture, nullptr, &maskRect);*/
	SDL_RenderCopy(renderer, playerTexture, nullptr, playerRect);
}

void GameStuff::displayActivists_Enemies(SDL_Texture* texture, SDL_Rect* rect)
{
	SDL_RenderCopy(renderer, texture, nullptr, rect);
}

void GameStuff::displayScreen()
{
	SDL_RenderPresent(renderer);
}

void GameStuff::destroySDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}