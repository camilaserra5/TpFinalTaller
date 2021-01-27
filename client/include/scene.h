#ifndef WOLFSTEIN_SCENE_H
#define WOLFSTEIN_SCENE_H

#include <SDL2/SDL.h>

class Scene {

public:
    Scene(SDL_Renderer *renderer);

    void prepareScene();

    void presentScene();

    void doInput();

    ~Scene();

private:
    SDL_Renderer *renderer;
};


#endif //WOLFSTEIN_SCENE_H
