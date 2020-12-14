#ifndef _JUGADOR_H
#define _JUGADOR_H

#include <vector>
#include <string>
#include "posicion.h"

class Arma;

class Jugador {
public:
    Jugador(std::string& nombre, int& id);

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

    Posicion &getPosicion(){ return this->posicion;}

    Arma* getArma(){return this->armaActual;}

    float getAnguloDeVista(){ return this->angulo;}

private:
    Posicion posicion = Posicion(1,1,1);
    int id;
    std::string nombre;
    int vida;
    int posx;
    int posy;
    std::vector<Arma *> armas;
    int balas;
    int puntaje;
    float angulo = 0;
    Arma* armaActual;
};

#endif
