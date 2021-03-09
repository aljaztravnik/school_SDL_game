#pragma once
#include <vector>
#include <SDL.h>

class Activist
{
protected:
	std::vector<SDL_Rect> activistRect;
	std::vector<int> activistDir;
	std::vector<int> activistDirCnt;
	std::vector<std::vector<int>> activistMoveTo;
	SDL_Texture* activistTexture;
public:
	~Activist();
	void displayActivists(SDL_Renderer* &);
};