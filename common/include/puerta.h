#ifndef __PUERTA__H
#define __PUERTA__H

#include "posicion.h"

class Puerta {
private:
    bool abierta;
    bool necesitaLlave;
    Posicion posicion;
    int fila;
    int columna;
    //contador para detectar el cierre de puertas
public:
    Puerta(bool necesitaLlave, Posicion posicion, int fila, int columna) : abierta(false), necesitaLlave(necesitaLlave),
                                                                           posicion(posicion),
                                                                           fila(fila), columna(columna) {}

    ~Puerta() {}

    void abrir();

    void cerrar();

    bool puedeSerAbierta(bool jugadorTieneLlave, double &distancia) const;

    double distanciaA(Posicion &posicion);

    bool estaAbierta();

    bool estaEnPosDelMapa(int &fila, int &columna);
};

#endif
