#include <stdio.h>
#include <SDL2/SDL.h>

extern bool init();
extern bool loadMedia();

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Surface *broker;

void close();

int main()
{
    if(!init()){
        printf("Failed to init!\n");
    } else {
        if(!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            SDL_BlitSurface(broker, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            SDL_Delay(4000);
        }
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
