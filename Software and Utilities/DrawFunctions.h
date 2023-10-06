#ifndef DRAW_FUNCTIONS_H
#define DRAW_FUNCTIONS_H

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

class DrawFunctions
{
public:
	DrawFunctions();
	~DrawFunctions();
	void drawCircle(SDL_Renderer* renderer, int x, int y, int radius);
	void fillCircle(SDL_Renderer* renderer, int x, int y, int radius, int color);
	void drawRect(SDL_Renderer* renderer, int x, int y, int width, int height);
	void fillRect(SDL_Renderer* renderer, int x, int y, int width, int height);

private:
};

#endif
