#include <stdio.h>
#include <SDL2/SDL.h>

#include "sim.h"

extern bool init();
extern bool loadMedia();

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern entity *broker;
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
    broker->redraw();
	SDL_UpdateWindowSurface(gWindow);    
	while(!quit) {
        while(SDL_PollEvent(&e) != 0){
            //User Requested a quit
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
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
