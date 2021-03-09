#include <iostream>
#include "activist.h"

Activist::~Activist()
{
	SDL_DestroyTexture(activistTexture);
}

void Activist::displayActivists(SDL_Renderer* &renderer)
{
	for (int i = 0; i < activistRect.size(); ++i)
		SDL_RenderCopy(renderer, activistTexture, nullptr, &activistRect[i]);
}