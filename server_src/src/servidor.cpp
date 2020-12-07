#include "../include/servidor.h"
#include <iostream>
#include <exception>
#include "SdlWindow.h"
#include "SdlTexture.h"

Servidor::Servidor(ProtectedQueue& cola_comandos):
      cola_comandos(cola_comandos){}

Servidor::~Servidor(){}

void procesar_comandos(ProtectedQueue& cola_comandos){
  bool termine = false;
  while (!termine){
    try{
      Comando* comando = cola_comandos.obtener_comando();
      comando->estrategia();
      //creamos actualizacion y la agregamos a una cola
      delete comando;
    }catch(const std::exception& exception){
      termine = true;
    }
  }
}
/*
void abrir_mapa(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *ventana = SDL_CreateWindow("LA VENTANITA",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED, 600, 400,
                                            SDL_WINDOW_SHOWN);
    SDL_Renderer *unRender = SDL_CreateRenderer(ventana,-1,0);

    SDL_SetRenderDrawColor(unRender, 0 , 255, 0, 255);
    SDL_RenderClear(unRender);
    SDL_RenderPresent(unRender);
    return 0;
}
*/
void Servidor::run(){
    bool termine = false;
    while (!termine){
        //el while va a depender del obtener comandos con un try catch
        //deberia haber un obtener comandos pero como lo tiene de atributo por ahora no
        procesar_comandos(this->cola_comandos);//devolveria actualizaciones
        //enviar_actualizaciones(cola de actualizaciones);
        //std::chrono::milliseconds duration(10);
        //std::this_thread::sleep_for(duration);
        termine = true;
    }
}
