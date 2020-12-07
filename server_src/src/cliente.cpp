#include "../include/cliente.h"
#include "movimiento.h"
#include "ataque.h"
#include "item_tomado.h"

#include <mutex>


Cliente::Cliente(ProtectedQueue& cola_comandos):
    cola_comandos(cola_comandos){}

Cliente::~Cliente(){}

void Cliente::run(){
    Comando* movimiento = new Movimiento();
    Comando* ataque = new Ataque();
    Comando* itemTomado = new ItemTomado();

    this->cola_comandos.aniadir_comando(movimiento);
    this->cola_comandos.aniadir_comando(ataque);
    this->cola_comandos.aniadir_comando(itemTomado);
}
