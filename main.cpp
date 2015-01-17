#include <stdio.h>
#include <SDL2/SDL.h>

extern bool init();
extern bool loadMedia();

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Surface *broker;

void close();

SDL_Rect brokerLoc;

int main()
{
    bool quit = false;
    SDL_Event e;
    if(!init()){
        printf("Failed to init!\n");
    } else {
        if(!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            SDL_BlitSurface(broker, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
        }
    }
    brokerLoc.w = 64;
    brokerLoc.h = 64;
    brokerLoc.x = 200;
    brokerLoc.y = 200;
    while(!quit) {
        while(SDL_PollEvent(&e) != 0){
            //User Requested a quit
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_BlitSurface(broker, NULL, gScreenSurface, &brokerLoc);
        SDL_UpdateWindowSurface(gWindow);
    }
    close();

    return 0;
}

void close()
{
    SDL_FreeSurface(broker);
    broker = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}
