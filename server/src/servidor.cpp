#include "../include/servidor.h"
#include <iostream>
#include <exception>
#include "actualizacion.h"
#include "jugador.h"

#define TIEMPO_SERVIDOR 30

// en si recibe un archivo yaml y luego sereializa;
Servidor::Servidor(Map *mapa, int cant_jugadores) :
        cola_comandos(),
        cola_actualizaciones(),
        jugadores(),
        estadoJuego(mapa),
        cant_jugadores(cant_jugadores),
        sigue_corriendo(true),
        arrancoPartida(false) {}

Servidor::~Servidor() {
    std::cout << "destructor servidor\n";
    std::map<int, Cliente *>::iterator it;
    for (it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
        it->second->join();
        delete it->second;
    }
}

void Servidor::procesar_comandos(ProtectedQueue<Comando *> &cola_comandos, EstadoJuego &estadoJuego) {
    bool termine = false;
    while (!termine) {
        try {
            Comando *comando = cola_comandos.obtener_dato();
            comando->ejecutar(estadoJuego);
            delete comando;
        } catch (const std::exception &exception) {
            termine = true;
        }
    }
}

void Servidor::agregarCliente(std::string &nombreJugador) {
    // asignarle un id random
    // el mapa deveria crear al jugador o hay que avisarle que hay un nuevo jugador
    // para asignarle posicion;
    //Jugador jugador(nombreJugador, id);
    int id = this->obtenerIdParaJugador();
    this->estadoJuego.agregarJugador(nombreJugador, id);
    std::cout << "agregue a un jugador\n\n";
    this->jugadores.insert(std::make_pair(id, cliente));
    if (this->jugadores.size() == this->cant_jugadores) {
        this->arrancoPartida = true;
        this->start();
    }
}

int Servidor::obtenerIdParaJugador() {
    int id = this->generadorDeId;
    this->generadorDeId += 1;
    return id;
}

void Servidor::lanzarJugadores() {
    for (auto it = this->jugadores.begin(); it != this->jugadores.end(); it++) {
        it->second->start();

    }
}

void Servidor::lanzarContadorTiempoPartida() {
    this->estadoJuego.lanzarContadorTiempoPartida();
}

void Servidor::actualizarContador() {
    this->estadoJuego.actualizarTiempoPartida();
}

bool Servidor::yaArranco() {
    return this->arrancoPartida;
}

bool Servidor::terminoPartida() {
    return !(this->sigue_corriendo);
}

ProtectedQueue<Comando *> &Servidor::obtenerColaEventos() {
    return this->cola_comandos;
}

ProtectedQueue<Actualizacion *> &Servidor::obtenerColaActualizaciones() {
    return this->cola_actualizaciones;
}

//servidor->deberia llamarse JuegoServer y despues le cambiamos a Juego
// servidor es partida

void Servidor::enviar_actualizaciones(ProtectedQueue<Actualizacion *> &actualizaciones) {
    //serializa y manda por sockets a cada jugador
    Actualizacion actualizacion(this->estadoJuego);
    this->cola_actualizaciones.aniadir_dato(&actualizacion);
}

void Servidor::run() {
    this->lanzarJugadores();
    this->lanzarContadorTiempoPartida();
    std::chrono::milliseconds duration(TIEMPO_SERVIDOR);
    std::this_thread::sleep_for(duration);
    while (this->sigue_corriendo) {
        //el while va a depender del obtener comandos con un try catch
        //deberia haber un obtener comandos pero como lo tiene de atributo por ahora no
        try {
            auto inicio = std::chrono::high_resolution_clock::now();
            procesar_comandos(this->cola_comandos, this->estadoJuego);
            this->enviar_actualizaciones(this->cola_actualizaciones);
            this->actualizarContador();
            if (this->estadoJuego.terminoPartida()) {
                this->arrancoPartida = false;
                this->sigue_corriendo = false;
            }
            auto fin = std::chrono::high_resolution_clock::now();
            auto delta = fin - inicio;
            long tardanza = delta.count();
            if (tardanza >= TIEMPO_SERVIDOR) {
                tardanza = TIEMPO_SERVIDOR;
            }
            std::chrono::milliseconds duration(30 - tardanza);
            std::this_thread::sleep_for(duration);

        } catch (...) {
            this->sigue_corriendo = false;

        }


    }
    //mostramos el ranking, podemos mandar una actualizacion con los jugadores que ganaron
    //  this->sigue_corriendo = false; creo que no va esta linea
}

std::vector<char> Servidor::serializar() {
    std::vector<char> informacion;
    std::vector<char> cantJugadoresAct = numberToCharArray(this->jugadores.size());
    informacion.insert(informacion.end(), cantJugadoresAct.begin(), cantJugadoresAct.end());
    std::vector<char> cantJugadores = numberToCharArray(cant_jugadores);
    informacion.insert(informacion.end(), cantJugadores.begin(), cantJugadores.end());
    return informacion;
}
