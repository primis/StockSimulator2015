#include <SDL2/SDL.h>
#include "sim.h"

#include <stdio.h>
extern SDL_Surface *gScreenSurface;

entity::~entity()
{
	SDL_FreeSurface(bitmap);
}

entity::entity()
{
    bitmap = NULL;
    location.y = 200;
    location.x = 200;
    location.h = 64;
    location.w = 64;
	bitmap = SDL_LoadBMP("media/broker.bmp");
	if (bitmap==NULL) {
		 printf( "Unable to load image. SDL Error: %s\n", SDL_GetError() );
	}
}
void entity::setBitmap(const char *bit)
{
	SDL_FreeSurface(bitmap);
	bitmap = SDL_LoadBMP(bit);
}
void entity::setPosition(int x, int y)
{
    location.x = x;
    location.y = y;
}

void entity::redraw()
{
    SDL_BlitSurface(bitmap, NULL, gScreenSurface, &location);
}

