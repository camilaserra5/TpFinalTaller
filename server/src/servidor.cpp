#include "../include/servidor.h"
#include <iostream>
#include <exception>
#include "actualizacion.h"
#include "jugador.h"

// en si recibe un archivo yaml y luego sereializa;
Servidor::Servidor(ProtectedQueue<Comando*> &cola_comandos, Map &mapa, int cant_jugadores) :
        cola_comandos(cola_comandos),
        jugadores(),
        estadoJuego(mapa, jugadores),
        cant_jugadores(cant_jugadores),
        sigue_corriendo(true){}

Servidor::~Servidor() {}

void procesar_comandos(ProtectedQueue<Comando*> &cola_comandos, EstadoJuego &estadoJuego) {
    bool termine = false;
    while (!termine) {
        try {
            Comando *comando = cola_comandos.obtener_comando(); // el comando va a tener quien le envio lo que tiene que hacer, osea el id
            /*Actualizacion actualizacion =*/ comando->estrategia(estadoJuego);//cambiar a ejecutar
            //creamos actualizacion y la agregamos a una cola
            delete comando;
        } catch (const std::exception &exception) {
            termine = true;
        }
    }
}
void Servidor::agregarCliente(std::string& nombreJugador, Cliente& cliente){
      // asignarle un id random
      // el mapa deveria crear al jugador o hay que avisarle que hay un nuevo jugador
      // para asignarle posicion;
      int id = 111;
      Jugador jugador(nombreJugador, id);
<<<<<<< HEAD
      this->jugadores.insert(std::pair<int, Jugador>(id,jugador));
=======
      this->jugadores.insert(std::make_pair(id,jugador));
>>>>>>> 7632d0ff7eb3384ad4fd780f34707e0a0d05d0fe

}

bool Servidor::yaArranco(){
    return this->sigue_corriendo;
}
bool Servidor::terminoPartida(){
    return !(this->sigue_corriendo);
}
ProtectedQueue& Servidor::obtenerColaEventos(){
    return this->cola_comandos;
}
//servidor->deberia llamarse JuegoServer y despues le cambiamos a Juego
// servidor es partida
void Servidor::run(){
    bool termine = false;
    while (!termine) {
        //el while va a depender del obtener comandos con un try catch
        //deberia haber un obtener comandos pero como lo tiene de atributo por ahora no
<<<<<<< HEAD
        //Jugador jugador;
        //this->jugadores.insert(std::pair<int, Jugador>(111, jugador));
=======
        std::string nombre = "juan";
        int id = 1;
        Jugador jugador(nombre,id);//nombre e id
        this->jugadores.insert(std::pair<int, Jugador>(111, jugador));
>>>>>>> 7632d0ff7eb3384ad4fd780f34707e0a0d05d0fe
        procesar_comandos(this->cola_comandos, this->estadoJuego);//devolveria actualizaciones
        //enviar_actualizaciones(cola de actualizaciones);
        //std::chrono::milliseconds duration(10);
        //std::this_thread::sleep_for(duration);
        termine = true;
    }
}
