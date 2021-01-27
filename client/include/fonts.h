//
// Created by cami on 27/1/21.
//

#ifndef WOLFSTEIN_FONTS_H
#define WOLFSTEIN_FONTS_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>


class Fonts {

public:
    Fonts();

    void addFont(std::string id, std::string path, int fontSize);

    TTF_Font *getFont(std::string id);

    ~Fonts();

private:
    std::map<std::string, TTF_Font *> fonts;
};

#endif //WOLFSTEIN_FONTS_H
