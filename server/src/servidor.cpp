#include "../include/servidor.h"
#include <iostream>
#include <exception>
#include "actualizaciones/actualizacion.h"
#include "jugador.h"
#include "actualizaciones/actualizacionInicioPartida.h"
#include "actualizaciones/actualizacionTerminoPartida.h"
#include "actualizaciones/actualizacionCambioArma.h"
#include "ranking.h"

#define TIEMPO_SERVIDOR 0.3

// en si recibe un archivo yaml y luego sereializa;
Servidor::Servidor(Map mapa, int cantJugadoresPosibles) :
        cola_comandos(),
        estadoJuego(mapa),
        cantJugadoresPosibles(cantJugadoresPosibles),
        sigue_corriendo(true),
        arrancoPartida(false) {}

Servidor::~Servidor() {}

void Servidor::procesar_comandos(ProtectedQueue<Comando *> &cola_comandos, EstadoJuego &estadoJuego) {
    bool termine = false;
    while (!termine) {
        try {
            Comando *comando = cola_comandos.obtener_dato();
            std::cerr << " proceso comando " << std::endl;
            std::vector<Actualizacion *> actualizaciones = comando->ejecutar(estadoJuego);
            // puede ser una lista de actualizaciones;
            // actualizacion partivulasr -> item comsumido(efecto, id, posicion, id jugador, pos jugador);
            delete comando;
            std::cerr << "enviar" << std::endl;
            this->enviar_actualizaciones(actualizaciones);
        } catch (const std::exception &exception) {
            termine = true;
        }
    }
}

void Servidor::agregarCliente(std::string &nombreJugador, ManejadorCliente *cliente, int &id) {
    // asignarle un id random
    // el mapa deveria crear al jugador o hay que avisarle que hay un nuevo jugador
    // para asignarle posicion;
    //Jugador jugador(nombreJugador, id);
    id = this->obtenerIdParaJugador();
    this->estadoJuego.agregarJugador(nombreJugador, id);
    cliente->settearId(id);
    this->clientes.insert({id, cliente});
    this->cantJugadoresAgregados++;
    if (this->cantJugadoresAgregados == this->cantJugadoresPosibles) {
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
    for (auto it = this->clientes.begin(); it != this->clientes.end(); ++it) {
        it->second->run();
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
/*
BlockingQueue<Actualizacion *> &Servidor::obtenerColaActualizaciones() {
    return this->cola_actualizaciones;
}
*/
//servidor->deberia llamarse JuegoServer y despues le cambiamos a Juego
// servidor es partida


void Servidor::enviar_actualizaciones(std::vector<Actualizacion *> actualizaciones) {
    //serializa y manda por sockets a cada jugador
    //Actualizacion *actualizacion = new Actualizacion(this->estadoJuego);
    // mandar una actualizaion en particular;
    std::cerr << " envio act " << std::endl;
    std::map<int, ManejadorCliente *>::iterator it;
    for (it = this->clientes.begin(); it != this->clientes.end(); ++it) {
        it->second->enviar_actualizaciones(actualizaciones);
    }
}

/*
void Servidor::generaComandosLua(){
  comando* comando = manejadorLua.procesar(this->estadoJuego); // servidor que tenga una intelgencia;
  this->cola_comandos.aniadir_dato(comando);
}*/

void Servidor::run() {
    this->lanzarJugadores();
    this->lanzarContadorTiempoPartida();
    std::vector<Actualizacion *> actualizaciones;
    actualizaciones.push_back(new ActualizacionInicioPartida(this->estadoJuego));
    this->enviar_actualizaciones(actualizaciones);

    //std::chrono::milliseconds duration(TIEMPO_SERVIDOR);
    //std::this_thread::sleep_for(duration);
    std::chrono::duration<double> tiempoServidor(TIEMPO_SERVIDOR);
    while (this->sigue_corriendo) {
        //el while va a depender del obtener comandos con un try catch
        //deberia haber un obtener comandos pero como lo tiene de atributo por ahora no
        try {
            auto inicio = std::chrono::high_resolution_clock::now();

            // generar comandos lua(this->cola_comandos, this->estadoJuego);
            //std::cerr << "proceso" << std::endl;
            procesar_comandos(this->cola_comandos, this->estadoJuego);
            this->actualizarContador();
            if (this->estadoJuego.terminoPartida()) {
                std::vector<Actualizacion *> actualizacionTermino;
                Actualizacion *terminoPartida = new ActualizacionTerminoPartida(this->estadoJuego);
                actualizacionTermino.push_back(terminoPartida);
                this->enviar_actualizaciones(actualizacionTermino);
                this->arrancoPartida = false;
                this->sigue_corriendo = false;
            }

            auto fin = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> sleepTime = tiempoServidor - (fin - inicio);
            //std::cerr << "sleep for" << time_span.count() << std::endl;
            std::this_thread::sleep_for(sleepTime);
            /*auto fin = std::chrono::high_resolution_clock::now();
            auto delta = fin - inicio;
            long tardanza = delta.count();
            if (tardanza >= TIEMPO_SERVIDOR) {
                tardanza = TIEMPO_SERVIDOR;
            }
            std::cerr << "sleep for" << TIEMPO_SERVIDOR-tardanza <<std::endl;
            std::chrono::milliseconds duration(TIEMPO_SERVIDOR - tardanza);
            std::this_thread::sleep_for(duration);
*/
        } catch (...) {
            this->sigue_corriendo = false;

        }


    }
    //mostramos el ranking, podemos mandar una actualizacion con los jugadores que ganaron
    //  this->sigue_corriendo = false; creo que no va esta linea
}

std::vector<char> Servidor::serializar() {
    std::vector<char> informacion;
    std::vector<char> cantJugadoresAct = numberToCharArray(this->cantJugadoresAgregados);
    informacion.insert(informacion.end(), cantJugadoresAct.begin(), cantJugadoresAct.end());
    std::vector<char> cantJugadores = numberToCharArray(this->cantJugadoresPosibles);
    informacion.insert(informacion.end(), cantJugadores.begin(), cantJugadores.end());
    return informacion;
}

void Servidor::joinClientes() {
    std::map<int, ManejadorCliente *>::iterator it;
    for (it = this->clientes.begin(); it != this->clientes.end(); ++it) {
        it->second->join();
    }
}
