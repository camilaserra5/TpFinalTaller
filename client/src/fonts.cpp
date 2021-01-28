#include "../include/fonts.h"

Fonts::Fonts() {

}

void Fonts::addFont(std::string id, std::string path, int fontSize) {
    this->fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font *Fonts::getFont(std::string id) {
    if (!fonts[id]) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return NULL;
    }
    return fonts[id];
}

Fonts::~Fonts() {

}
