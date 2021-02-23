#include <comandos/desconectarJugador.h>
#include "../include/partida.h"
#include "actualizaciones/actualizacionInicioPartida.h"
#include "actualizaciones/actualizacionTerminoPartida.h"
#include "config.h"

#define TIEMPO_SERVIDOR 0.3
#define ID_LUA 777

#define ARRIBA 3
#define ABAJO 4
#define ROTAR_DERECHA 1
#define ROTAR_IZQUIERDA 2

#define LUA MODULO_LUA "modulo.lua"

// en si recibe un archivo yaml y luego sereializa;
Partida::Partida(Map&& mapa, int cantJugadoresPosibles, ConfiguracionPartida configuracion) :
        cola_comandos(),
        estadoJuego(std::move(mapa), configuracion),
        cantJugadoresPosibles(cantJugadoresPosibles),
        sigue_corriendo(true),
        arrancoPartida(false) {}

Partida::~Partida() {
    // libero todos los comandos que no pudieron mandarse

    std::cerr << "entre al destructor de partida\n";
    bool termine = false;
    while (!termine) {
        try {
            Comando *comando = cola_comandos.obtener_dato();
            delete comando;
        } catch (const std::exception &exception) {
            termine = true;
        }
    }
}

void Partida::procesar_comandos(EstadoJuego &estadoJuego) {
    std::map<int, ThClient *>::iterator it;
    for (it = this->clientes.begin(); it != this->clientes.end(); ++it) {
        if (it->second->is_dead() && !estadoJuego.estaMuerto(it->second->getId())) {
            std::cerr << "desconecto jugador " << it->second->getId() << std::endl;
            auto desconectarJugador = new DesconectarJugador(it->second->getId());
            this->cola_comandos.aniadir_dato(desconectarJugador);
        }
    }
    bool termine = false;
    while (!termine) {
        try {
            Comando *comando = cola_comandos.obtener_dato();
            std::vector<Actualizacion *> actualizaciones = comando->ejecutar(estadoJuego);
            delete comando;
            this->enviar_actualizaciones(actualizaciones);
        } catch (const std::exception &exception) {
            termine = true;
        }
    }
}

void Partida::agregarCliente(std::string &nombreJugador, ThClient *cliente) {
    std::cerr << "Partida agrega un Jugador" << std::endl;
    this->estadoJuego.agregarJugador(nombreJugador, cliente->getId());
    this->clientes.insert({cliente->getId(), cliente});
    this->cantJugadoresAgregados++;
    if (this->cantJugadoresAgregados == this->cantJugadoresPosibles) {
        this->arrancoPartida = true;
        this->start();
    }

}

void Partida::lanzarJugadores() {
    for (auto it = this->clientes.begin(); it != this->clientes.end(); ++it) {
        it->second->start();
    }
}

void Partida::lanzarContadorTiempoPartida() {
    this->estadoJuego.lanzarContadorTiempoPartida();
}

void Partida::actualizarContador() {
    this->estadoJuego.actualizarTiempoPartida();
}

bool Partida::yaArranco() {
    return this->arrancoPartida;
}

bool Partida::terminoPartida() {
    return !(this->sigue_corriendo);
}

ProtectedQueue<Comando *> &Partida::obtenerColaEventos() {
    return this->cola_comandos;
}


void Partida::enviar_actualizaciones(std::vector<Actualizacion *> actualizaciones) {

    std::map<int, ThClient *>::iterator it;
    for (it = this->clientes.begin(); it != this->clientes.end(); ++it) {
        if (!it->second->is_dead()) {
            it->second->enviar_actualizaciones(actualizaciones);
        }
    }
    this->ultAct = actualizaciones;

}

void Partida::finalizarClientes() {
    std::map<int, ThClient *>::iterator it;
    for (it = this->clientes.begin(); it != this->clientes.end(); ++it) {
        it->second->stop();
    }
}

void Partida::generarComandosLua(JugadorLua &jugadorLua) {
    Comando *nuevoComando;
    char teclaComando = jugadorLua.procesar();
    switch (teclaComando) {
        case 'w':
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ARRIBA));
            std::cerr << "=== SE MUEVE PARA ARRIBA LUA==== " << std::endl;
            break;
        case 'd':
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ROTAR_DERECHA));
            std::cerr << "=== ROTA A DERECHA LUA==== " << std::endl;
            break;
        case 's':
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ABAJO));
            std::cerr << "=== SE MUEVE ABAJO LUA==== " << std::endl;
            break;
        case 'a':
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ROTAR_IZQUIERDA));
            std::cerr << "=== ROTA A IZQUIERDA LUA==== " << std::endl;
            break;
        case 'p':
            nuevoComando = new Ataque(jugadorLua.id);
            std::cerr << "=== ATACA LUA==== " << std::endl;
            break;
        default:
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ROTAR_DERECHA));
            std::cerr << "=== mov default LUA==== " << std::endl;
            break;
    }
    this->cola_comandos.aniadir_dato(nuevoComando);
}

void Partida::run() {
    std::cerr << "=== CREO JUGADOR LUA==== " << std::endl;
    std::string ruta(LUA);

//    JugadorLua jugadorLua(this->estadoJuego, ID_LUA, ruta);
  //  std::string nombre("IA");
  //  jugadorLua.instanciarJugador(nombre);

    this->lanzarJugadores();
    this->lanzarContadorTiempoPartida();
    std::vector<Actualizacion *> actualizaciones;
    std::vector<char> informacion = this->estadoJuego.serializar();
    Actualizacion *act = new ActualizacionInicioPartida(informacion);
    actualizaciones.push_back(act);
    this->enviar_actualizaciones(actualizaciones);

    std::chrono::duration<double> tiempoPartida(3);


    while (this->sigue_corriendo) {

        try {
            auto inicio = std::chrono::high_resolution_clock::now();
          //  std::cerr << "=== GENERO COMANDOS LUA==== " << std::endl;
          //  generarComandosLua(jugadorLua);
            procesar_comandos(this->estadoJuego);
            this->actualizarContador();
            if (this->estadoJuego.terminoPartida()) {
                std::vector<Actualizacion*> actualizacionTermino;
                Actualizacion *terminoPartida = new ActualizacionTerminoPartida(this->estadoJuego.obtenerJugadores());
                actualizacionTermino.push_back(terminoPartida);
                this->enviar_actualizaciones(actualizacionTermino);
                this->arrancoPartida = false;
                this->sigue_corriendo = false;
            }

            auto fin = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> sleepTime = tiempoPartida - (fin - inicio);
            std::this_thread::sleep_for(sleepTime);

            for (auto &actu : this->ultAct) {
                if (actu != NULL) {
                  delete actu;
                  actu = NULL;
                }
            }
        } catch (...) {
            std::cerr << "ENTRE AL CATCH" << std::endl;
            this->sigue_corriendo = false;
            for (auto &actu : this->ultAct) {
              if (actu != NULL) {
                delete actu;
                actu = NULL;
              }
            }
        }
    }
    std::cerr << "sigue corriendo: " << this->sigue_corriendo << std::endl;
  //  std::cerr << "borro :" << act->obtenerId() << std::endl;
    //delete act;
}

std::vector<char> Partida::serializar() {
    std::vector<char> informacion;
    std::vector<char> cantJugadoresAct = numberToCharArray(this->cantJugadoresAgregados);
    informacion.insert(informacion.end(), cantJugadoresAct.begin(), cantJugadoresAct.end());
    std::vector<char> cantJugadores = numberToCharArray(this->cantJugadoresPosibles);
    informacion.insert(informacion.end(), cantJugadores.begin(), cantJugadores.end());
    return informacion;
}

void Partida::joinClientes() {
    std::map<int, ThClient *>::iterator it;
    for (it = this->clientes.begin(); it != this->clientes.end(); ++it) {
        it->second->join();
    }
}

void Partida::stop(){
    this->sigue_corriendo = false;
}
