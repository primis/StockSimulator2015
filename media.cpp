#include <stdio.h>
#include <SDL2/SDL.h>
#include "sim.h"
entity *broker;
background *bg;
bool loadMedia()
{
    bool success = true;
	broker = new entity;
    bg = new background;
    return success;
}
