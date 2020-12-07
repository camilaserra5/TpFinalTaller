#ifndef JUEGO_H
#define JUEGO_H
#include <SDL2/SDL.h>

class Juego{
    private:
        bool corriendo;
        SDL_Window *ventana;
        SDL_Renderer *render;
    public:
        Juego(){}
        ~Juego(){}
        void inicializar(const char* titulo, int xpos, int ypos, int ancho, int alto, bool fullscreen);

        bool estaCorriendo(){return corriendo;}
        void handleEvents();
        void actualizar();
        void renderizar();
        void clean();
};

#endif /*JUEGO_H*/