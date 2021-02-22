#ifndef WOLFSTEIN_SCENE_H
#define WOLFSTEIN_SCENE_H

#include <SDL2/SDL.h>

class Scene {

public:
    /*
      * crea la clase scene dejandola valida para uso
    */
    Scene(SDL_Renderer *renderer);
    /*
      * prepara la escena
    */
    void prepareScene();
    /*
      * presenta la escena
    */
    void presentScene();
    /*
      * verifica los evnetos que llegan 
    */
    void doInput();
    /*
      * liberra la clas escena con sus recursos
    */
    ~Scene();

private:
    SDL_Renderer *renderer;
};


#endif //WOLFSTEIN_SCENE_H
