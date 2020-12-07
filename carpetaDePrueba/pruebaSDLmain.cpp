#include <SDL2/SDL.h>
/*#include <SDL2/SDL_image.h>
#include <string>
*/
int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *ventana = SDL_CreateWindow("LA VENTANITA", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer *unRender = SDL_CreateRenderer(ventana,-1,0);

    SDL_SetRenderDrawColor(unRender, 0 , 255, 0, 255);
    SDL_RenderClear(unRender);
    SDL_RenderPresent(unRender);
    return 0;
}