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

void Servidor::run(){
    bool termine = false;
    while (!termine){
        //el while va a depender del obtener comandos con un try catch
        //deberia haber un obtener comandos pero como lo tiene de atributo por ahora no
        procesar_comandos(this->cola_comandos);//devolveria actualizaciones
        //enviar_actualizaciones();
        //std::chrono::milliseconds duration(10);
        //std::this_thread::sleep_for(duration);
        termine = true;
    }
}
