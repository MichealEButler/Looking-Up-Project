#include "DrawFunctions.h"

DrawFunctions::DrawFunctions()
{

}

DrawFunctions::~DrawFunctions()
{

}

void DrawFunctions::drawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int x0 = 0;
    int y0 = radius;
    int d = 3 - 2 * radius;
    if (!radius) return;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    while (y0 >= x0)
    {
        SDL_RenderDrawPoint(renderer, x - x0, y - y0);
        SDL_RenderDrawPoint(renderer, x - y0, y - x0);
        SDL_RenderDrawPoint(renderer, x + y0, y - x0);
        SDL_RenderDrawPoint(renderer, x + x0, y - y0);
        SDL_RenderDrawPoint(renderer, x - x0, y + y0);
        SDL_RenderDrawPoint(renderer, x - y0, y + x0);
        SDL_RenderDrawPoint(renderer, x + y0, y + x0);
        SDL_RenderDrawPoint(renderer, x + x0, y + y0);
        if (d < 0) d += 4 * x0++ + 6;
        else d += 4 * (x0++ - y0--) + 10;
    }
}

void DrawFunctions::fillCircle(SDL_Renderer* renderer, int x, int y, int radius, int color)
{
    int _color = color;
    int x0 = 0;
    int y0 = radius;
    int d = 3 - 2 * radius;
    if (!radius) return;

    switch (_color) {
    case 1:
        //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red (elm+beech)
        SDL_SetRenderDrawColor(renderer, 61, 145, 71, 255); //dark green (spruce)
        break;
    case 2:
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green (pine)
        //SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); //cyan (larch)
        break;
    case 3:
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue
        break;
    case 4:
        SDL_SetRenderDrawColor(renderer, 255, 178, 102, 255); // light orange
        break;
    case 5:
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // yellow
        break;
    case 6:
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255); // brown
        break;
    case 7:
        SDL_SetRenderDrawColor(renderer, 51, 255, 51, 255); // lime
        break;
    case 8:
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); // grey
        break;
    default:
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    auto drawline = [&](int sx, int ex, int ny)
    {
        for (int i = sx; i < ex; i++)
            SDL_RenderDrawPoint(renderer, i, ny);
    };

    while (y0 >= x0)
    {
        drawline(x - x0, x + x0, y - y0);
        drawline(x - y0, x + y0, y - x0);
        drawline(x - x0, x + x0, y + y0);
        drawline(x - y0, x + y0, y + x0);
        if (d < 0) d += 4 * x0++ + 6;
        else d += 4 * (x0++ - y0--) + 10;
    }

}

void DrawFunctions::drawRect(SDL_Renderer* renderer, int x, int y, int width, int height)
{
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, x, y, x + width, y);
    SDL_RenderDrawLine(renderer, x + width, y, x + width, y + height);
    SDL_RenderDrawLine(renderer, x + width, y + height, x, y + height);
    SDL_RenderDrawLine(renderer, x, y + height, x, y);
}

void DrawFunctions::fillRect(SDL_Renderer* renderer, int x, int y, int width, int height)
{
    int x2 = x + width;
    int y2 = y + height;

    if (x < 0) x = 0;
    if (x >= 800) x = 800;
    if (y < 0) y = 0;
    if (y >= 800) y = 800;

    if (x2 < 0) x2 = 0;
    if (x2 >= 800) x2 = 800;
    if (y2 < 0) y2 = 0;
    if (y >= 800) y2 = 800;

    for (int i = x; i < x2; i++)
    {
        for (int j = y; j < y2; j++)
        {
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }
}
