#ifndef __sim_h
#define __sim_h

class entity
{
    public:
        entity();
        ~entity();
		void setBitmap(const char* bit);
        void setPosition(int x, int y);
        void redraw();
    private:
        SDL_Surface *bitmap;
        SDL_Rect location;
};

#endif
