#ifndef _JUGADOR_H
#define _JUGADOR_H

#include <vector>
#include <string>
#include "posicion.h"

class Arma;

class Jugador {
public:
    Jugador(std::string &nombre, int &id);

    ~Jugador();

    void moverse(int posx, int posy);

    void actualizar_vida(int &vidaActualizada);

    void agregar_item();

    void agregar_arma(Arma *arma);

    int cantidad_balas();

    int puntos_de_vida();

    void agregar_balas(int &balas);

    int posEnX();

    int posEnY();

    int getId();

    void setPosicion(Posicion &posicion){this->posicion = posicion;}

    Posicion &getPosicion() { return this->posicion; }

    Arma *getArma() { return this->armaActual; }

    float getAnguloDeVista() { return this->posicion.getAnguloDeVista(); }

    //void setAnguloDeVista(float anguloJugador){this->angulo = anguloJugador; }

    bool tengollave(){
        return (this->llaves > 0);
    }

    void usarLlave(){
        this->llaves += -1;
    }

    bool estaMuerto(){
        return (this->vida <=0);
    }

    bool poseeArma(Arma* arma);

    void agarrarLlave();

    void sumarPuntos(int puntos);

private:
    Posicion posicion;
    int id;
    std::string nombre;
    int vida;
    std::vector<Arma *> armas;
    int balas;
    int puntaje;
    float angulo = 0;
    Arma *armaActual;
    int llaves;
    int cantidad_vidas;
};

#endif
