#include "../include/juego.h"

int main(){
    Juego* juego = new Juego();

    juego->inicializar("Wolfstein", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while(juego->estaCorriendo()){
        juego->handleEvents();
        juego->actualizar();
        juego->renderizar();
    }
    juego->clean();
    return 0;
}