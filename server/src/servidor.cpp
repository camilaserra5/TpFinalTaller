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
#define ID_LUA 777

#define ARRIBA 3
#define ABAJO 4
#define ROTAR_DERECHA 1
#define ROTAR_IZQUIERDA 2

// en si recibe un archivo yaml y luego sereializa;
Servidor::Servidor(Map mapa, int cantJugadoresPosibles) :
        cola_comandos(),
        estadoJuego(mapa),
        cantJugadoresPosibles(cantJugadoresPosibles),
        sigue_corriendo(true),
        arrancoPartida(false){}

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

void Servidor::generarComandosLua(JugadorLua& jugadorLua, ProtectedQueue<Comando *> &cola_comandos){
    Comando* nuevoComando;
    char teclaComando = jugadorLua.procesar();
    switch(teclaComando){
        case 'w':
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ARRIBA));
            break;
        case 'd':
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ROTAR_DERECHA));
            break;
        case 's':
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ABAJO));
            break;
        case 'a':
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ROTAR_IZQUIERDA));
            break;
        case 'p':
            nuevoComando = new Ataque(jugadorLua.id);
            break;
        default:
            nuevoComando = new Movimiento(jugadorLua.id, static_cast<Accion>(ROTAR_DERECHA));
            break;
    }
    this->cola_comandos.aniadir_dato(nuevoComando);
}

void Servidor::run() {
    std::cerr << "=== CREO JUGADOR LUA==== " << std::endl;
    std::string ruta("modulo.lua");

    JugadorLua jugadorLua(this->estadoJuego, ID_LUA, ruta);
    std::string nombre("IA");
    jugadorLua.instanciarJugador(nombre);
    
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
            std::cerr << "=== GENERO COMANDOS LUA==== " << std::endl;
            generarComandosLua(jugadorLua, this->cola_comandos);
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
