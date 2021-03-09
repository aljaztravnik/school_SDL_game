#include <iostream>
#include <string>
#include "commonFunctions.h"


bool CommonFunctions::valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool CommonFunctions::rectOverlap(SDL_Rect &A, SDL_Rect &B)
{
	bool xOverlap = valueInRange(A.x, B.x, B.x + B.w) ||
		valueInRange(B.x, A.x, A.x + A.w);

	bool yOverlap = valueInRange(A.y, B.y, B.y + B.h) ||
		valueInRange(B.y, A.y, A.y + A.h);

	return xOverlap && yOverlap;
}

