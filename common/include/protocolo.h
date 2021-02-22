#ifndef _PROTOCOLO_H
#define _PROTOCOLO_H


#include "socket.h"

#include "comandos/ataque.h"
#include "comandos/movimiento.h"
#include "comandos/aperturaDePuerta.h"
#include "comandos/cambioDeArma.h"
#include <iostream>
#include <netinet/in.h>
#include <cstring>

#define TAMANIO 100

class Protocolo {
public:
    /*
      * creara el protocolo dejnadola valido para uso
      * el socket debe ser valido
    */
    Protocolo(Socket socket);
    /*
      * liberara la clase
    */
    ~Protocolo();
    /*
      * envia la informacion por medio de  un socket , primero enviando el
      *tamanio y luego lo que  contiene
    */
    void enviar(std::vector<char> &informacion);
    /*
      * recibe la informacion por medio de un socket
      * y lo devuleve en un vector de char
    */
    std::vector<char> recibir_aux();
    /*
      * recibe por medio del socket
    */
    std::vector<char> recibir();
    /*
      * deseriala el comando y lo devuelve creado
    */
    Comando *deserializarComando(std::vector<char> &informacion);
    /*
      * deserializamos el item y se lo devuelve
    */
    Item *deserializarItem(std::vector<char> &informacion);
    /*
      * se cierra el protocolo cerrando el socket
    */  
    void cerrar();


private:
    Socket socket;
};

#endif
