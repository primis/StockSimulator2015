#ifndef __sim_h
#define __sim_h

class entity
{
    public:
        entity();
        ~entity();
		void setBitmap(const char* bit);
        void setPosition(int x, int y);
		void setSize(int w, int h);
        void redraw();
    private:
        SDL_Surface *bitmap;
        SDL_Rect location;
};

class background
{
    public:
        background();
        ~background();
        void redraw();
    private:
        entity *bgarray[10][8];
};
class fchar
{
	public:
		fchar(char c, int, int, bool);
		~fchar();
		void redraw();
	private:
		entity *letter;
};
class fstring
{
    public:
        fstring();
        ~fstring();
		void setText(const char *, bool);
		void setPosition(int x, int y);
        void redraw();
        bool isHit(int x, int y);
    private:
        int posX;
        int posY;
        char const *inttext;
        fchar *charArray[32];
};


#endif
