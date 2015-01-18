#include <stdio.h>
#include <time.h>
#include "sim.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT= 480;

SDL_Window  *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;


bool init()
{
    bool success = true;
	srand (time(NULL));
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO |  SDL_INIT_TIMER)>0) {
        printf("SDL ERRORL %s\n",SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("Stock Market Simulator 2015", SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_FULLSCREEN /*SDL_WINDOW_SHOWN*/);
        if(gWindow == NULL) {
            printf("Window Could not be created! SDL_ERROR: %s\n",SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    SDL_UpdateWindowSurface(gWindow);
	// Startup Menus!
	fstring* title = new fstring();
	fstring* intro = new fstring();
	fstring* intro2 = new fstring();
	fstring* intro3 = new fstring();
	title->setPosition(150,50);
		title->setText("stock market simulator 2015", true);
	intro->setPosition(180,100);
		intro->setText("collect the money", true);
	intro2->setPosition(150,120);	
		intro2->setText("avoid the toxic asset stocks", true);
	intro3->setPosition(200,140);
		intro3->setText("watch the timer", true);
	title->redraw();	
	intro->redraw();
	intro2->redraw();
	intro3->redraw();
	SDL_UpdateWindowSurface(gWindow);
	SDL_Delay(5000);
    return success;
}

