#ifndef WOLFSTEIN_BACKGROUND_H
#define WOLFSTEIN_BACKGROUND_H

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <string>

class Background {

public:
    Background(std::string backgroundImg, SDL_Renderer *renderer);

    void drawBackground();

    ~Background();

private:
    SDL_Texture *background;
    SDL_Renderer *renderer;

};


#endif //WOLFSTEIN_BACKGROUND_H
