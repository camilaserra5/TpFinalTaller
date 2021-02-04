#include "../include/background.h"
#include "../include/logInWindow.h"

#define TEXTURE_BACKGROUND_ROOT "../../resources/images/background.png"

Background::Background(std::string backgroundImage, SDL_Renderer *renderer) : renderer(renderer) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", backgroundImage.c_str());
    background = IMG_LoadTexture(this->renderer, backgroundImage.c_str());
}

void Background::drawBackground() {
    SDL_Rect dest;
    for (int x = 0; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;
        SDL_RenderCopy(this->renderer, this->background, NULL, &dest);
    }
}

Background::~Background() {}
