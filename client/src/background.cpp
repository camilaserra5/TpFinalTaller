#include "../include/background.h"
#include "../include/logInWindow.h"

Background::Background(std::string backgroundImage, SDL_Renderer *renderer, int screenWidth, int screenHeight) :
        renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", backgroundImage.c_str());
    background = IMG_LoadTexture(this->renderer, backgroundImage.c_str());
}

void Background::drawBackground() {
    SDL_Rect dest;
    for (int x = 0; x < screenWidth; x += screenWidth) {
        dest.x = x;
        dest.y = 0;
        dest.w = screenWidth;
        dest.h = screenHeight;
        SDL_RenderCopy(this->renderer, this->background, NULL, &dest);
    }
}

Background::~Background() {}
