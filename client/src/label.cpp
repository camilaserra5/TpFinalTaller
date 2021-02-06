
#include "../include/label.h"
#include <iostream>

Label::Label(int xpos, int ypos, std::string text, TTF_Font *font, SDL_Color &color, SDL_Renderer *renderer) :
        label(text), font(font), textColor(color), renderer(renderer) {
    this->pos.x = xpos;
    this->pos.y = ypos;
}

void Label::actualizarTexto(std::string texto) {
    this->label = texto;
}

void Label::setLabelText() {

    SDL_Surface *surface = TTF_RenderText_Blended(font, label.c_str(), textColor);
    labelTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(labelTexture, nullptr, nullptr, &pos.w, &pos.h);
}

void Label::draw() {
    SDL_RenderCopy(renderer, labelTexture, nullptr, &pos);
}

int Label::getTexto() {
    return std::stoi(this->label);
}

Label::~Label() {

}
