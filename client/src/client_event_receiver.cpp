#include "../include/client_event_receiver.h"
#include "socket.h"

#include <utility>
#include <algorithm>
#include <vector>

ClientEventReceiver::ClientEventReceiver(Socket &socket,
                                         ProtectedQueue<Actualizacion *> &updates, Modelo &modelo) :

        socket(socket), updates(updates), modelo(modelo) {}

void ClientEventReceiver::run() {
    while (this->running) {
        Actualizacion *update;
        // debería ser un protocolo en realidad
        //this->protocolo.recibir();
        //this->updates.aniadir_dato(update);
        // datos de jugador sacado de lo ue se recibe;
        //std::vector<char> informacion = protocolo.recibir();
        //primero mapa/
        //despues items
        //despues jugadores
        int x = 1;
        int y = 2;
        int vida = 10;
        int angulo = 50;
        int id;
        this->modelo.actualizarJugador(x, y, vida, angulo, id/*arma*/, 1);


        /*
          for (int i= 0; i<cantEntidades; i++){
                int id;
                Estado estado;
               Type tipoDeObjeto;
               int posx;
               int posy;
               this->modelo.actualizarEntidad(id, tipoDeObjeto, posx, posy, estado);
          }
          */
    }
}

void ClientEventReceiver::cerrar() {
    this->running = false;
}

ClientEventReceiver::~ClientEventReceiver() {
    this->running = false;
    this->join();
}
