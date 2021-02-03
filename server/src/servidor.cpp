#include "../include/servidor.h"
#include <iostream>
#include <exception>
#include "actualizacion.h"
#include "jugador.h"


// en si recibe un archivo yaml y luego sereializa;
Servidor::Servidor(/*ProtectedQueue<Comando*> &cola_comandos,ProtectedQueue<Actualizacion>& actualizaciones,*/
        Map *mapa, int cant_jugadores) :
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

void Servidor::agregarCliente(std::string &nombreJugador, Cliente *cliente) {
    // asignarle un id random
    // el mapa deveria crear al jugador o hay que avisarle que hay un nuevo jugador
    // para asignarle posicion;
    int id = 111;
    //Jugador jugador(nombreJugador, id);
    this->estadoJuego.agregarJugador(nombreJugador, id);
    this->jugadores.insert(std::make_pair(id, cliente));
    if (this->jugadores.size() == this->cant_jugadores) {
        this->arrancoPartida = true;
        this->start();
    }
}

void Servidor::lanzarJugadores() {
    for (auto it = this->jugadores.begin(); it != this->jugadores.end(); it++) {
        it->second->start();

    }
}

void Servidor::lanzarContadorTiempoPartida() {
    this->estadoJuego.lanzarContadorTiempoPartida();
}
void Servidor::actualizarContador(){
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

ProtectedQueue<Actualizacion> &Servidor::obtenerColaActualizaciones() {
    return this->cola_actualizaciones;
}

//servidor->deberia llamarse JuegoServer y despues le cambiamos a Juego
// servidor es partida

void Servidor::enviar_actualizaciones(ProtectedQueue<Actualizacion> &actualizaciones) {
    //serializa y manda por sockets a cada jugador
    Actualizacion actualizacion(this->estadoJuego);
    this->cola_actualizaciones.aniadir_dato(actualizacion);
}

void Servidor::run() {
    this->lanzarJugadores();
    this->lanzarContadorTiempoPartida();
    bool termine = false;
    std::chrono::milliseconds duration(30);
    std::this_thread::sleep_for(duration);
    while (!termine) {
        //el while va a depender del obtener comandos con un try catch
        //deberia haber un obtener comandos pero como lo tiene de atributo por ahora no
        try {
            procesar_comandos(this->cola_comandos, this->estadoJuego);
            this->enviar_actualizaciones(this->cola_actualizaciones);
            this->actualizarContador();
            if(this->estadoJuego.terminoPartida()){
                termine = true;
                this->sigue_corriendo= false;
            }
        } catch (...) {
            this->sigue_corriendo = false;
            termine = true;
        }

        //std::chrono::milliseconds duration(10);
        //std::this_thread::sleep_for(duration);
        termine = true;
    }
    //mostramos el ranking, podemos mandar una actualizacion con los jugadores que ganaron
    //  this->sigue_corriendo = false; creo que no va esta linea
}
