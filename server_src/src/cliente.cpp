#include "../include/cliente.h"
#include "../common_src/include/movimiento.h"
#include "../common_src/include/ataque.h"
#include "../common_src/include/item_catch.h"

#include <mutex>


Cliente::Cliente(ProtectedQueue& cola_comandos):
    cola_comandos(cola_comandos){}

Cliente::~Cliente(){}

void Cliente::run(){
    Comando* movimiento = new Movimiento();
    Comando* ataque = new Ataque();
    Comando* item = new Item_catch();

    this->cola_comandos.aniadir_comando(movimiento);
    this->cola_comandos.aniadir_comando(ataque);
    this->cola_comandos.aniadir_comando(item);
}
