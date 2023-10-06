#include "Display.h"
#include "Input.h"

Input* input1 = nullptr;

Display::Display()
{

}

Display::~Display()
{

}

void Display::initDisplay(const char* title, int x, int y, int w, int h, bool isShown, int iteration, int scale, std::string dir)
{
    std::string outFile = dir + "Output/Run1.txt";
    input1 = new Input();
    //input1->storeASC("Input/testinput2.txt", 700, 1000);
    input1->storeOutFile(outFile.c_str(), h, w, 0, iteration, dir);

    isCPressed = false;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << std::endl << "Display initialised . . . " << std::endl;

        window = SDL_CreateWindow(title, x, y, w*scale, h*scale, SDL_WINDOW_SHOWN);
        if (window)
        {
            std::cout << "Window created . . . " << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer created . . . " << std::endl;
        }

        isRunning = true;
    }
    else {
        isRunning = false;
    }

}

void Display::handleEvents()
{
    SDL_Event e;

    SDL_PollEvent(&e);

    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_RETURN)
        {
            isRunning = false;
        }

        if (e.key.keysym.sym == SDLK_c)
        {
            isCPressed = true;
        }

        if (e.key.keysym.sym == SDLK_x)
        {
            isCPressed = false;
        }
    }

    if (e.type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void Display::updateDisplay()
{

}

void Display::clearRenderer()
{
    SDL_RenderClear(renderer);
}

void Display::renderDisplay(int iteration, int w, int h, int state, std::string dir)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    if (state == 1)
    {
        input1->renderInput3(renderer);
    }
    if (state == 2)
    {
        input1->renderInput2(renderer);
    }

    saveImage(renderer, iteration, w, h, dir);
}

void Display::renderPresent()
{
    SDL_RenderPresent(renderer);
    //SDL_Delay(1000); // change timing in order to breifly view the output for each iteration
}

void Display::cleanDisplay()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Display cleaned . . . " << std::endl << std::endl;
}

bool Display::running()
{
    return isRunning;
}

bool Display::cPressed()
{
    return isCPressed;
}

void Display::saveImage(SDL_Renderer* renderer, int iteration, int w, int h, std::string dir)
{
    const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
    const int width = w;
    const int height = h;
    std::string p1 = dir + "Output/Map";
    std::string p2 = ".bmp";
    std::string file = p1 + std::to_string(iteration) + p2;

    const char* cfilename = file.c_str();

    //SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, format);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, format, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface, cfilename);
    SDL_FreeSurface(surface);
}
