#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Display
{
public:
	Display();
	~Display();
	void initDisplay(const char* title, int x, int y, int w, int h, bool isShown, int iteration, int scale, std::string dir);
	void handleEvents();
	void updateDisplay();
	void renderDisplay(int iteration, int w, int h, int state, std::string dir); // state 1 or 2 depending on scaling
	void renderPresent();
	void clearRenderer();
	void cleanDisplay();

	bool running();
	bool cPressed();

	void saveImage(SDL_Renderer* renderer, int iteration, int w, int h, std::string dir);

	SDL_Renderer* renderer;

private:
	SDL_Window* window;
	SDL_Rect* srcR, destR;
	SDL_RendererInfo rendererInfo;

	bool isCPressed;
	bool isRunning;

};

#endif
