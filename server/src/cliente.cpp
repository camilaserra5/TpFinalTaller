#include "../include/old_cliente.h"
#include "comandos/movimiento.h"
#include "comandos/ataque.h"


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
    printf("me llega una actualizacion\n");
}

void Cliente::run() {

    int id = 111;
    Comando *movimiento = new Movimiento(id, Accion::moverDerecha);
    Comando *ataque = new Ataque(id);

    this->cola_comandos.aniadir_dato(movimiento);
    this->cola_comandos.aniadir_dato(ataque);
    std::cout << "agrege comandos a cola\n";
    std::chrono::milliseconds duration(1100);
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
