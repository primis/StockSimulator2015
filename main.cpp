#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
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
bool quit = false;
void close();
fstring *score;
stock *ticker[1000000]; // Maximize! of them out at once on the feild.
int last_stock;
Uint32 start = 0;
int launch;

void game_over()
{
	bg->redraw();
	fstring *over = new fstring;
	over->setPosition(200,200);
	over->setText("game over", true);
    SDL_UpdateWindowSurface(gWindow);
	SDL_Delay(5000);	
	quit = true;
}

void launchAStock()
{
	printf("Launching!\n");
	if(last_stock<10) {
		ticker[last_stock++] = new stock;
	} else {
		int i;
		for(i=0;i<10;i++) {
			if(ticker[i] == NULL) {
				ticker[i] = new stock;
				break;
			}
		}
	}
}

int main()
{
    last_stock = 0;
    SDL_Event e;
    if(!init()){
        printf("Failed to init!\n");
    } else {
        if(!loadMedia()) {
            printf("Failed to load media!\n");
        }
    }
    
	start = SDL_GetTicks();
	launch = 500;	

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
			posY-=2;
		}		
		if(currentKeyStates[SDL_SCANCODE_DOWN])
		{
			posY+=2;
		}
		if(currentKeyStates[SDL_SCANCODE_LEFT])
		{
			posX-=2;
		}
		if(currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			posX+=2;
		}
		if(currentKeyStates[SDL_SCANCODE_A])
		{
			launchAStock();
		}
		if(currentKeyStates[SDL_SCANCODE_SPACE])
		{
			shooting = true;
			BposX = posX+2;
			BposY = posY+2;
		    shootsound = true;
        }
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
        int s;
        bool tempbool;
        for(s=0;s<last_stock;s++) {
            if(ticker[s] != NULL) {
          		if(shooting) {
                    tempbool = ticker[s]->isHit(BposX+8,BposY+10);
                    if(tempbool) {
                        delete ticker[s];
                        ticker[s] = NULL;
                        hitsound = true;
						continue;
                    }
                }
                tempbool = ticker[s]->rise(posX,posY);
                if(!tempbool) {
					if(ticker[s]->getValue()<0) {                    
						game_over();
					} else {
						score += ticker[s]->getValue();
						delete ticker[s];
						ticker[s] = NULL;
						continue;
					}		
                }
				//SDL_Delay(1);                
				ticker[s]->redraw();
            }
			if(SDL_GetTicks() - start > launch) {
				launchAStock();
				start = SDL_GetTicks();
				//launch = rand() % 300 * 10;
			}	
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
