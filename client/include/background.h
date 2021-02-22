#ifndef WOLFSTEIN_BACKGROUND_H
#define WOLFSTEIN_BACKGROUND_H

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <string>

class Background {

public:
    /*
      * creara la clase background dejandola valida para uso
    */
    Background(std::string backgroundImg, SDL_Renderer *renderer, int screenWidth, int screenHeight);

    /*
      * dibujara la correspondiente imagen en el fondo de la pantalla
    */
    void drawBackground();

    /*
      * liberara la clase background junto a sus recursos
    */
    ~Background();

private:
    SDL_Texture *background;
    SDL_Renderer *renderer;
    int screenWidth;
    int screenHeight;
};


#endif //WOLFSTEIN_BACKGROUND_H
