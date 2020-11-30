#include "../include/servidor.h"
#include <iostream>
#include <exception>
#include "../common_src/include/SdlWindow.h"
#include "../common_src/include/SdlTexture.h"

Servidor::Servidor(const std::queue<SDL_Event>& cola_eventos):
      cola_eventos(cola_eventos){}

Servidor::~Servidor(){}

void Servidor::run(){

    bool termine = false;
    while (!termine){
        try{
          int x = 0, y = 0;
            SDL_Event evento = this->cola_eventos.front();
            this->cola_eventos.pop();
            switch(evento.type) {
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvento = (SDL_KeyboardEvent&) evento;
                    switch (keyEvento.keysym.sym) {
                        case SDLK_LEFT:
                            x -= 10;
                            std::cout << "me enviaron la tecla izquierda";
                            break;
                        case SDLK_RIGHT:
                            x += 10;
                            std::cout << "me llego la tecla derecha";
                            break;
                        case SDLK_UP:
                            y -= 10;
                            std::cout << " me llego tecla de arriba";
                            break;
                        case SDLK_DOWN:
                            y += 10;
                            std::cout << "me llego tecla de abajo";
                            break;
                        }
                  }
                  break;
                    case SDL_MOUSEMOTION:
                        std::cout << "soy el mouse" << std::endl;
                        break;
                    case SDL_QUIT:
                        std::cout << "tecla salir" << std::endl;
                        //running = false;
                        break;
                }
      }catch(const std::exception& exception){
            //std::cerr << exception.what();
            termine = true;
      }
    }
}
