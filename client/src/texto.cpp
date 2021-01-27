#include "../include/texto.h"

/*
Texto::Texto(Ventana& ventana): ventana(ventana){
      const char* fuente = "../../client/resources/fuentes/Nougat.ttf"
      int tamanio = 12;
      this->font = TTF_OpenFont(fuente, tamanio);
      this->actualColor = {255, 255, 255};
      SDL_Surface* mensaje = TTF_RenderText_Blended_Wrapped(fuente, text.c_str(), colorActual, ventana.getAncho());
      int ancho, largo;
      TTF_SizeText(font, text.c_str(), &ancho, &largo);
      SDL_Texture* textura_aux = SDL_CreateTextureFromSurface(ventana.getRenderer(), mensaje);
      SDL_FreeSurface(mensaje);
      this->text_texture = Texture(textura_aux, ventana));
}
*/
