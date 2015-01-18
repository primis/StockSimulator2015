#include "sim.h"
/*

COLLECT GREEN
DESTROY RED
GOOD LUCK

*/
fstring::fstring()
{
	char buff[32];
	posX = 0;
	posY = 0;
	inttext = "score 0000000";
    
	sprintf(buff, inttext);
	for (int i=0;i < strlen(inttext); i++) {    
		charArray[i] = new fchar(buff[i],posX+(i*15),posY, true);
    }
}
void fstring::setText(const char *text, bool red)
{
	inttext = text;
	char buff[30];
	sprintf(buff, inttext);
	for (int i=0;i < strlen(inttext); i++) {    
		charArray[i] = new fchar(buff[i],posX+(i*15),posY, red);
    }
}

void fstring::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}

fstring::~fstring()
{
    int i;
    for(i=0;i>strlen(inttext);i++) {
        delete charArray[i];
	}
}

void fstring::redraw()
{    
	int i;
   for(i=0;i<strlen(inttext);i++) {
        charArray[i]->redraw();
    }
}

bool fstring::isHit(int x, int y) 
{
	if((y > posY) && (y < posY+50)) {
		if((x > posX) && (x < (posX + 50)))  {		
            return true;
		}
	}
    return false;
}


fchar::fchar(char c, int x, int y, bool red)
{
	char buffer[32];	
	letter = new entity;
	if(red) {
		sprintf(buffer, "media/font/red/%c.bmp", c);
	} else	{
		sprintf(buffer, "media/font/green/%c.bmp", c);
	}	
	letter->setBitmap(buffer);
	letter->setPosition(x,y);
}

fchar::~fchar()
{
	delete letter;
}

void fchar::redraw()
{
	letter->redraw();
}
