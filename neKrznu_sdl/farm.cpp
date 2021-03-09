#include <iostream>
#include "farm.h"

Farm::Farm()
{
	if (TTF_Init() == -1) std::cout << "Failed to initialize SDL_ttf.\n";
	arial = TTF_OpenFont("arial.ttf", 14);
	white = { 255,255,255,255 };
	spawnFarms();
}

Farm::~Farm()
{
	SDL_DestroyTexture(farmTexture);
	SDL_FreeSurface(numOfAnimals);
}

void Farm::spawnFarms()
{
	SDL_Rect tmpRect{ 0,0,200,100 };
	for (int i = 0; i < 5; i++)
	{
		tmpRect.x = rand() % ((1280 - (tmpRect.w + 51))) + (tmpRect.w + 51);
		tmpRect.y = rand() % (720 - ((2 * tmpRect.h) + 1)) + ((2 * tmpRect.h) + 1);
		farmRect.push_back(tmpRect);
		animalsInFarm.push_back(5);
	}
}

void Farm::deleteFarm(int i)
{
	farmRect.erase(farmRect.begin() + i);
	animalsInFarm.erase(animalsInFarm.begin() + i);
}

void Farm::displayFarms(SDL_Renderer* &renderer)
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