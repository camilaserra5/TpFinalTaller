#include "../include/cliente.h"
#include "comandos/movimiento.h"
#include "comandos/ataque.h"
#include "comandos/item_tomado.h"

#include <mutex>


Cliente::Cliente(ProtectedQueue<Comando *> &cola_comandos, ProtectedQueue<Actualizacion> &actualizaciones,
                 std::string &nombre) :
        cola_comandos(cola_comandos),
        cola_actualizaciones(actualizaciones),
        nombre(nombre) {}

Cliente::~Cliente() {

}

void Cliente::actualizar(const Actualizacion &actualizacion) {
    //actualizacion.actualizar_vista
    //desp sacar lo que sigue
    printf("me llega una actualizacion");
}

void Cliente::run() {
    int tipo_de_movimiento = 1;
    int id = 111;
    Comando *movimiento = new Movimiento(id, tipo_de_movimiento);
    Comando *ataque = new Ataque(id);
    Comando *itemTomado = new ItemTomado(id);

    this->cola_comandos.aniadir_dato(movimiento);
    this->cola_comandos.aniadir_dato(ataque);
    this->cola_comandos.aniadir_dato(itemTomado);
    std::cout << "agrege comandos a cola";
    std::chrono::milliseconds duration(10);
    std::this_thread::sleep_for(duration);

    bool termine = false;
    while (!termine) {
        try {
            Actualizacion actualizacion = this->cola_actualizaciones.obtener_dato();
            this->actualizar(actualizacion);
        } catch (...) {
            termine = true;
        }
    }
}
