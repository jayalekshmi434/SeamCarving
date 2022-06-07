#include<iostream>
#include<SDL2/SDL.h>
#include<string>

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

class detectKey{
    public:

        enum keyPress {
            KEY_PRESS_UP,
            KEY_PRESS_DOWN,
            KEY_PRESS_LEFT,
            KEY_PRESS_RIGHT,
            KEY_PRESS_ESC
        };
        detectKey();
        ~detectKey();
        void handleInput(bool running);
    private:
        SDL_Event event;
        const Uint8* state ;
        SDL_Window* window=nullptr;
        SDL_Surface* gScreenSurface;
        SDL_Surface* imageSurface;
        SDL_Renderer * renderer ;
        SDL_Texture * texture;
};
