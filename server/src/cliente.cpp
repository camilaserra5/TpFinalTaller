#include "../include/cliente.h"
#include "movimiento.h"
#include "ataque.h"
#include "item_tomado.h"

#include <mutex>


Cliente::Cliente(ProtectedQueue &cola_comandos) :
        cola_comandos(cola_comandos) {}

Cliente::~Cliente() {}

void Cliente::run() {
    int tipo_de_movimiento = 1;
    int id = 111;
    Comando *movimiento = new Movimiento(id, tipo_de_movimiento);
    Comando *ataque = new Ataque(id);
    Comando *itemTomado = new ItemTomado(id);

    this->cola_comandos.aniadir_comando(movimiento);
    this->cola_comandos.aniadir_comando(ataque);
    this->cola_comandos.aniadir_comando(itemTomado);
}
