#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "../../common/include/socket.h"
#include "protected_queue.h"
#include "blocking_queue.h"
#include "comandos/comando.h"
#include <SDL2/SDL.h>
#include <actualizaciones/actualizacion.h>
#include <config.h>


#define ARCHIVO_DE_CONFIGURACION CLIENT_DIR "config.yaml"

class Cliente {

public:
    /*
      * creara al cliente dejandolo valido para uso
    */
    Cliente(std::string configFile);
    /*
      * liberara al cliente con sus recursos
    */
    ~Cliente();
    /*
      * ejecutara el programa, creando la pantalla de login, y lanzara el juego
      * y los hilos de neviar y recibir. Sera el encargado de cerrar el rpograma
      * y hacer join de los hilos
    */   
    void run();

private:
    std::string configFile = ARCHIVO_DE_CONFIGURACION;
    Socket socket;
    bool corriendo;

};

#endif
