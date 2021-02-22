#ifndef WOLFSTEIN_FONTS_H
#define WOLFSTEIN_FONTS_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>


class Fonts {

public:
    /*
      *  crea la clase fonts dejandola valida para uso
    */
    Fonts();
    /*
      * crea una fuente y la agregra al mapa de fuentes
    */
    void addFont(std::string id, std::string path, int fontSize);
    /*
      * devuelve una fuente de acuerdo al id correspondiente
    */  
    TTF_Font *getFont(std::string id);

    ~Fonts();

private:
    std::map<std::string, TTF_Font *> fonts;
};

#endif //WOLFSTEIN_FONTS_H
