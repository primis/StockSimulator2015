#include <stdio.h>
#include <SDL2/SDL.h>
#include "sim.h"
entity *broker;
background *bg;
entity *bullet;
bool loadMedia()
{
    bool success = true;
	broker = new entity;
    bg = new background;
	bullet = new entity;
	bullet->setBitmap("media/circle.bmp");
	bullet->setSize(16,16);
    return success;
}
