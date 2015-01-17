#include <stdio.h>
#include <SDL2/SDL.h>

#include "sim.h"

extern bool init();
extern bool loadMedia();

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern entity *broker;
extern background *bg;
void close();


int main()
{
    bool quit = false;
    SDL_Event e;
    if(!init()){
        printf("Failed to init!\n");
    } else {
        if(!loadMedia()) {
            printf("Failed to load media!\n");
        }
    }
    bg->redraw();
    broker->redraw();
    int posX=0;
	int posY=200;
	broker->setPosition(posX,posY);
    SDL_UpdateWindowSurface(gWindow);    
	while(!quit) {
        while(SDL_PollEvent(&e) != 0){
            //User Requested a quit
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if(currentKeyStates[SDL_SCANCODE_UP])
		{
			posY--;
		}		
		if(currentKeyStates[SDL_SCANCODE_DOWN])
		{
			posY++;
		}
		if(currentKeyStates[SDL_SCANCODE_LEFT])
		{
			posX--;
		}
		if(currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			posX++;
		}
        broker->setPosition(posX,posY);
        bg->redraw();
        broker->redraw();
        SDL_UpdateWindowSurface(gWindow);
    }
    close();

    return 0;
}

void close()
{
    delete broker; 

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}
