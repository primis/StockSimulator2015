#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "sim.h"

extern bool init();
extern bool loadMedia();


extern Mix_Music *bgm;
extern Mix_Chunk *hitFX, *dropFX;

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern entity *broker;
extern background *bg;
extern entity *bullet;
void close();
fstring *score;

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
    
	score = new fstring();
    int posX=300;
	int posY=0;
	int BposX, BposY;
	bool shooting = false;
	bool shootsound = false;
    bool hitsound = false;

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
		if(currentKeyStates[SDL_SCANCODE_SPACE])
		{
			shooting = true;
			BposX = posX+2;
			BposY = posY+2;
		    shootsound = true;
        }

		// Render Time, 1 ms delay.
	//	SDL_Delay(1);
        broker->setPosition(posX,posY);		
		bullet->setPosition(BposX,BposY++);
        bg->redraw();
        broker->redraw();
		
	// Conditionals
		if(posY>240) {
			posY=240;
		}	// Hardline bottom at 320
		if(posY<0) {
			posY=0;
		}		
		if(posX>624) {
			posX=624;
		}
		if(posX<0) {
			posX=0;
		}		


        score->redraw();	

	
		if(shooting) {
			if(BposY>640) {
				shooting = false;
			}
			bullet->redraw();
		}
		SDL_UpdateWindowSurface(gWindow);
     // Sound
        if(Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(bgm, -1);
        }
        if(shootsound) {
            shootsound = false;
            Mix_PlayChannel(-1, dropFX, 0);
        }
        if(hitsound) {
            hitsound = false;
            Mix_PlayChannel(-1, hitFX, 0);
        }
    }
    close();

    return 0;
}

void close()
{
    delete broker; 
    delete bullet;
    delete bg;
	delete score;
    Mix_FreeMusic(bgm);
    Mix_FreeChunk(dropFX);
    Mix_FreeChunk(hitFX);

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    Mix_Quit();
    SDL_Quit();
}
