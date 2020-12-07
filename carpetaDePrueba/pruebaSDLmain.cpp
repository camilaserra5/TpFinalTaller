#include "juego.h"
/*#include <SDL2/SDL_image.h>
#include <string>

void crearVentana(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *ventana = SDL_CreateWindow("LA VENTANITA", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer *unRender = SDL_CreateRenderer(ventana,-1,0);

    SDL_SetRenderDrawColor(unRender, 0 , 255, 0, 255);
    SDL_RenderClear(unRender);
    SDL_RenderPresent(unRender);
    SDL_Delay(6000);
}*/
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