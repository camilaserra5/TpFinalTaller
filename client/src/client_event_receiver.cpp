#include "../include/client_event_receiver.h"
#include "socket.h"
#include "map.h"
#include "items/item.h"
#include "jugador.h"
#include "estadoJuego.h"

#include <utility>
#include <algorithm>
#include <vector>
#include <map>

ClientEventReceiver::ClientEventReceiver(Socket& socket,
                                         ProtectedQueue<Actualizacion *> &updates, Modelo &modelo, int idJugador) :

        protocolo(std::move(socket)), updates(updates), modelo(modelo), idJugador(idJugador) {}

void ClientEventReceiver::run() {
    while (this->running) {
      //  Actualizacion *update;
        // debería ser un protocolo en realidad
        //this->protocolo.recibir();
        //this->updates.aniadir_dato(update);
        // datos de jugador sacado de lo ue se recibe;
        //std::vector<char> informacion = protocolo.recibir();
        //primero mapa/
        //despues items
        //despues jugadores
          std::vector<char> informacion = this->protocolo.recibir();
        /*  char jugadoresSize = informacion[0];
          int index = 1;
          for (int i = 0; i < jugadoresSize; i++) {

              if (idJugador == informacion[1]){
                  int posx = informacion[2];
                  int posy = informacion[3];
                  int vida = informacion[4];
                  int angulo = informacion[5];
                  int idArma = informacion[6];
                  bool disparando = informacion[7];
                  int puntaje = informacion[8];
                  int cantVidas = informacion[9];
                  int balas = informacion[10];
                  modelo.actualizarJugador(posx, posy, vida, angulo, idArma,
                                          disparando, puntaje, cantVidas, balas);
              }

              modelo.actualizarEnemigos(posx, posy, vida, disparando, idArma);

          }*/
          EstadoJuego* estadoJuego;
          estadoJuego->deserializar(informacion);
          std::map<int, Jugador*> jugadores = estadoJuego->obtenerJugadores();
          std::map<int, Jugador*>::iterator it;
          Jugador* jugador = jugadores.at(idJugador);
          int vida = jugador->puntos_de_vida();
          int posx = jugador->getPosicion().pixelesEnX();
          int posy = jugador->getPosicion().pixelesEnY();
          int angulo = jugador->getAnguloDeVista();
          int idArma = jugador->getArma()->getId();
          int puntaje = jugador->obtenerLogro().obtener_puntaje();
          bool disparando = jugador->estaDisparando();
          int cantVidas = jugador->puntos_de_vida();
          int balas = jugador->cantidad_balas();
          modelo.actualizarJugador(posx, posy, vida, angulo, idArma,
                                  disparando, puntaje, cantVidas, balas);
          for (it = jugadores.begin(); it != jugadores.end(); it++){
              if (it->first != idJugador){
                    int idE = it->first;
                    int vidaE = it->second->puntos_de_vida();
                    int posxE = it->second->getPosicion().pixelesEnX();
                    int posyE = it->second->getPosicion().pixelesEnY();
                    int idArmaE = idArma;
                    int anguloJugador = angulo;
                    int anguloE = it->second->getAnguloDeVista();
                    bool disparandoE = it->second->estaDisparando();
                    modelo.actualizarEnemigo(idE, vidaE, disparandoE, posxE,
                                              posyE, idArmaE, anguloJugador,
                                              anguloE);
              }
          }

          Map* mapa = estadoJuego->obtenerMapa();
          std::vector<Item*> items = mapa->obtenerItems();
          for (int i = 0; i< items.size(); i++){
              Item* item = items[i];
              int idI = item->getId();
              int posxI = item->obtenerPosicion().pixelesEnX();
              int posyI = item->obtenerPosicion().pixelesEnY();
              modelo.actualizarObjeto(idI, posxI, posyI);
          }

      }
}

void ClientEventReceiver::cerrar() {
    this->running = false;
}

ClientEventReceiver::~ClientEventReceiver() {
    this->running = false;
    this->join();
}
