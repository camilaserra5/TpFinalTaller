#include "../include/juego.h"
#include <iostream>
int main() {
    Juego *juego = new Juego();
    try{
        juego->inicializar("Wolfstein", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
        while (juego->estaCorriendo()) {
            juego->handleEvents();
            juego->actualizar();
            juego->renderizar();
        }
        juego->clean();
    }catch(...){
        std::cout<<"error";
    }

    return 0;
}