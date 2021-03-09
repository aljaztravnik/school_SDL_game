#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include "SDL_ttf.h"

class Farm
{
protected:
	std::vector<SDL_Rect> farmRect;
	std::vector<int> animalsInFarm;
	SDL_Texture* farmTexture;
	TTF_Font* arial;
	SDL_Color white;
	SDL_Surface* numOfAnimals;
public:
	Farm();
	~Farm();
	void spawnFarms();
	void deleteFarm(int);
	void displayFarms(SDL_Renderer* &);
};