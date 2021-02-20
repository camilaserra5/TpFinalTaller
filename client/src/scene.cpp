#include "../include/scene.h"

Scene::Scene(SDL_Renderer *renderer) : renderer(renderer) {}

Scene::~Scene() {}

void Scene::prepareScene() {
    SDL_SetRenderDrawColor(this->renderer, 96, 128, 255, 255);
}

void Scene::presentScene() {
    SDL_RenderPresent(this->renderer);
}


void Scene::doInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;

            default:
                break;
        }
    }
}