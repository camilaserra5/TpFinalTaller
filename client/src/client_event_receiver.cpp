#include "../include/client_event_receiver.h"
#include "socket.h"
#include "map.h"
#include "items/item.h"
#include "jugador.h"
#include "estadoJuego.h"
#include "actualizacion.h"

#include <utility>
#include <algorithm>
#include <vector>
#include <map>

ClientEventReceiver::ClientEventReceiver(Protocolo *protocolo,
                                         ProtectedQueue<Actualizacion *> &updates, Modelo &modelo, int idJugador) :

        protocolo(protocolo), updates(updates), modelo(modelo), idJugador(idJugador), corriendo(true) {}

void ClientEventReceiver::run() {
    while (this->corriendo) {
        try {
            std::vector<char> informacion = this->protocolo->recibir();

            Actualizacion *actualizacion = new Actualizacion();
            actualizacion->deserializar(informacion);
          /*  this->updates.aniadir_dato(actualizacion);
            std::cerr << "METO UPDATE EN LA COLA\n";
*/

            EstadoJuego& estadoJuego = actualizacion->obtenerEstadoJuego();
            std::map<int, Jugador *> jugadores = estadoJuego.obtenerJugadores();
            std::map<int, Jugador *>::iterator it;
            Jugador *jugador;
            for (it = jugadores.begin(); it != jugadores.end(); ++it) {
                if (idJugador == it->second->getId()) {
                    jugador = it->second;
                }
            }
            int vida = jugador->puntos_de_vida();
            int posx = jugador->getPosicion().pixelesEnX();
            int posy = jugador->getPosicion().pixelesEnY();
            int angulo = jugador->getAnguloDeVista();
            int idArma = jugador->getArma()->getId();
            int puntaje = jugador->obtenerPuntosTotales();
            bool disparando = jugador->estaDisparando();
            int cantVidas = jugador->cant_de_vida();
            int balas = jugador->cantidad_balas();
            std::cerr << "parametros: " << vida << " -" << posx<< " -"  << posy<< "- "  << angulo<< " -"  << idArma<< "- "  << puntaje<< " -"  << disparando<< "- "  << cantVidas<< " "  << balas  << " " << "\n";

            modelo.actualizarJugador(posx, posy, vida, angulo, idArma,
                                     disparando, puntaje, cantVidas, balas);
            for (it = jugadores.begin(); it != jugadores.end(); it++) {
                if (it->second->getId() != idJugador) {
                    int idE = it->first;
                    int vidaE = it->second->puntos_de_vida();
                    int posxE = it->second->getPosicion().pixelesEnX();
                    int posyE = it->second->getPosicion().pixelesEnY();
                    int idArmaE = idArma;
                    int anguloJugador = angulo;
                    int anguloE = it->second->getAnguloDeVista();
                    bool disparandoE = it->second->estaDisparando();
                    int puntajeE = it->second->obtenerPuntosTotales();
                    modelo.actualizarEnemigo(idE, vidaE, disparandoE, posxE,
                                             posyE, idArmaE, anguloJugador,
                                             anguloE, puntajeE);
                }
            }

            Map& mapa = estadoJuego.obtenerMapa();
            std::vector<Item *> items = mapa.obtenerItems();
            for (int i = 0; i < items.size(); i++) {
                Item *item = items[i];
                int idI = item->getId();
                Type tipo = item->getTipo();
                int posxI = item->obtenerPosicion().pixelesEnX();
                int posyI = item->obtenerPosicion().pixelesEnY();
                modelo.actualizarObjeto(idI, tipo, posxI, posyI);
            }
            if (actualizacion->terminoPartida()) {
                std::vector<int> ordenRanking = actualizacion->obtenerRanking();
                modelo.terminoPartida(ordenRanking);
            }
            delete actualizacion;
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            std::cerr << "fallooooooooo no recibo mas \n";

            this->corriendo = false;
        }

    }
}

void ClientEventReceiver::cerrar() {
    this->corriendo = false;
}

ClientEventReceiver::~ClientEventReceiver() {
    this->corriendo = false;
    this->join();
}
