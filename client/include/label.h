#ifndef WOLFSTEIN_LABEL_H
#define WOLFSTEIN_LABEL_H

#include "fonts.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Label {
public:
    /*
      * creara la clase label dejandola valida para uso
      * debe recibir sus parametros inicalizados
    */
    Label(int xpos, int ypos, std::string text, TTF_Font *font, SDL_Color &color, SDL_Renderer *renderer);
    /*
      * settea el texto que va a renderizar
    */
    void setLabelText();
    /*
      * actualiza el texto que va a renderizar
    */
    void actualizarTexto(std::string texto);
    /*
      * dibuja el texto correspondiente
    */
    void draw();
    /*
      * devuelve el texto
    */
    int getTexto();
    /*
      * libera la clase label junto a sus recursos
    */  
    ~Label();

private:
    SDL_Rect pos;
    std::string label;
    TTF_Font *font;
    SDL_Color textColor;
    SDL_Texture *labelTexture;
    SDL_Renderer *renderer;
};


#endif //WOLFSTEIN_LABEL_H
