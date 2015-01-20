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
fstring *ticktoc;
stock *ticker[1000]; // Maximize! of them out at once on the feild.
int last_stock;
int numscore = 10000;
Uint32 start = 0;
int launch;
unsigned int times = 600;

void game_over()
{
	bool blink = true;
	int x = 0;
	bg->redraw();
	fstring *over = new fstring;
	
	char buff[50];	
	over->setPosition(240,200);
	over->setText("game over", true);
	while(x < 20)	{
		x++;
		if(numscore > 0 && blink) {
			sprintf(buff, "score %d", numscore);
			blink = false;
		} else if(numscore > 0) {
			sprintf(buff, "score");
			blink = true;
		} else {
			sprintf(buff, "you went bankrupt");
		}
		score->setPosition(0,0);
		score->setText(buff,true);
		score->redraw();
		over->redraw();
	    SDL_UpdateWindowSurface(gWindow);
		SDL_Delay(250);
	}
	printf("Score: %d\n", numscore);
	quit = true;
}

void launchAStock()
{
	times--;
	if(times > 50) {
		times = 50;
	}
	int i;
	if(last_stock<9) {
		ticker[last_stock++] = new stock;
	} 
    
    else {
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
    int i;
	for(i=0;i<1000;i++) {
		ticker[i] = NULL;	
	}
	start = SDL_GetTicks();
	launch = 500;	
	ticktoc = new fstring();
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
		if(currentKeyStates[SDL_SCANCODE_Q])
		{
			game_over();
		}
		if(currentKeyStates[SDL_SCANCODE_SPACE])
		{
			shooting = true;
			BposX = posX+2;
			BposY = posY+2;
		    shootsound = true;
        }      
		broker->setPosition(posX,posY);		
		BposY += 4;
        bullet->setPosition(BposX,BposY);
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
                        if(ticker[s]->getValue() < 0) {				
                            hitsound = true;
                            numscore += (-1*(ticker[s]->getValue() / 5));					
						}                        
						delete ticker[s];
                        ticker[s] = new stock;
						continue;
                    }
                }
                tempbool = ticker[s]->rise(posX,posY);
                if(!tempbool) {
					if(ticker[s]->getY() > 5) {
                    	numscore += ticker[s]->getValue();
						hitsound = true;
					}
                    delete ticker[s];
                    ticker[s] = new stock;
                    continue;
                }           
				ticker[s]->redraw();		
            }
        }
		if(numscore < 0) {
			numscore = -1;
			game_over();
		}	
   		if(SDL_GetTicks()%50 == 0) {
			launchAStock();
		}
        char tempbuff[25];
        sprintf(tempbuff,"score %09d",numscore);
            score->setText(tempbuff,true);
            score->redraw();	
        sprintf(tempbuff,"time %04d",(SDL_GetTicks()/10)-600);
	        ticktoc->setPosition(400,0);
            ticktoc->setText(tempbuff,true);
            ticktoc->redraw();

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
		if(SDL_GetTicks() > 81000) {
			game_over();
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
	delete ticktoc;
    Mix_FreeMusic(bgm);
    Mix_FreeChunk(dropFX);
    Mix_FreeChunk(hitFX);

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    Mix_Quit();
    SDL_Quit();
}
