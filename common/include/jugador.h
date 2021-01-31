#ifndef _JUGADOR_H
#define _JUGADOR_H

#include <vector>
#include <string>
#include "posicion.h"
#include "logro.h"
#include <map>

class Arma;

class Jugador {
public:
    Jugador(std::string &nombre, int &id);

    ~Jugador();

    void moverse(int posx, int posy);

    void rotar();

    void actualizar_vida(int &vidaActualizada);

    void agregar_item();

    void agregar_arma(Arma *arma);

    int cantidad_balas();

    int puntos_de_vida();

    void agregar_balas(int &balas);

    int posEnX();

    int posEnY();

    int getId();

    void setPosicion(Posicion &posicion);

    Posicion &getPosicion();

    Arma *getArma();

    float getAnguloDeVista();

    void actualizarArma();

    //void setAnguloDeVista(float anguloJugador){this->angulo = anguloJugador; }

    bool tengollave();

    void usarLlave();

    bool estaMuerto();

    bool poseeArma(Arma *arma);

    void agarrarLlave();

    void sumarPuntos(int puntos);

    void gastarBalas(int cantidadDeBalas);

    Logro &obtenerLogro();

    void aniadirEnemigosMatados(int jugadoresMatados);

    std::vector<char> serializar() {
        std::vector<char> informacion;

        return informacion;
    }

    void deserializar(std::vector<char>& serializado) {}

// juagdor serializacion;
    // id -> int;
    // pos -> 2 ini
    // nomnre -> string -> primeor longitud (int) y luego los bytes(chars);
private:
    Posicion posicion;
    int id;
    std::string nombre;
    int vida;
    std::map<int,Arma*> armas;
    int balas;
    float angulo = 0;
    float velocidadDeRotacion;
    Arma *armaActual;
    int llaves;
    int cantidad_vidas;
    Logro logro;
};

#endif
