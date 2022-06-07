#include "detectKey.h"
#include <iostream>


detectKey::detectKey()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        //SDL_EnableUNICODE(1);
    }
    
   
        window = SDL_CreateWindow("SDL2 Displaying Image",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_BORDERLESS);
       // gScreenSurface = SDL_GetWindowSurface( window );
           // imageSurface =IMG_Load( "../Data/index.jpeg");
            //renderer = SDL_CreateRenderer(window, -1, 0);
            //texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
            //SDL_RenderCopy(renderer, texture, NULL, NULL);
            //SDL_RenderPresent(renderer);

            //SDL_BlitSurface(imageSurface,NULL,gScreenSurface,NULL);

}
detectKey::~detectKey()
{
    SDL_FreeSurface(imageSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
}

void detectKey::handleInput(bool running)
{
    SDL_Event e;
    while(running){
    while (SDL_PollEvent(&e))
    {   
        if (e.type == SDL_QUIT)
        {   
            running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {   std::cout << "0" << std::endl;
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                std::cout << "1" << std::endl;
                break;

            case SDLK_DOWN:
                std::cout << "2" << std::endl;
                break;

            case SDLK_LEFT:
                std::cout << "3" << std::endl;
                break;

            case SDLK_RIGHT:
                std::cout << "4" << std::endl;
                break;
            }
        }
    }
    }
}


