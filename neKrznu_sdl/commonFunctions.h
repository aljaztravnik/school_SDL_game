#pragma once
#include <SDL.h>
#include <string>

class CommonFunctions
{
protected:
public:
	bool valueInRange(int, int, int);
	bool rectOverlap(SDL_Rect &, SDL_Rect &);
};