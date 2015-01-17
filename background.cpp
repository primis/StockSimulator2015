#include <SDL2/SDL.h>
#include "sim.h"

background::background()
{
    int x, y;
    for(x=0;x<10;x++) {
        for(y=0;y<8;y++) {
            bgarray[x][y] = new entity;
            bgarray[x][y]->setPosition(x*64,y*64);
            bgarray[x][y]->setBitmap("media/tile.bmp");
        }
    }
}
background::~background()
{
    int x, y;
    for(x=0;x<10;x++) {
        for(y=0;y<8;y++) {
            delete bgarray[x][y];
        }
    }
}
void background::redraw()
{
    int x, y;
    for(x=0;x<10;x++) {
        for(y=0;y<8;y++) {
            bgarray[x][y]->redraw();
        }
    }
}
