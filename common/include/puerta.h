#ifndef __PUERTA__H
#define __PUERTA__H

#include "posicion.h"
#include "iserializable.h"

class Puerta : public ISerializable{
private:
    bool abierta;
    bool necesitaLlave;
    Posicion posicion;
    int fila;
    int columna;
    //contador para detectar el cierre de puertas
public:
    Puerta(bool necesitaLlave, Posicion posicion, int fila, int columna, bool abierta) : abierta(abierta), necesitaLlave(necesitaLlave),
                                                                           posicion(posicion),
                                                                           fila(fila), columna(columna) {}
    Puerta(){}                                                                       
    ~Puerta() {}

    void abrir();

    void cerrar();

    bool puedeSerAbierta(bool jugadorTieneLlave, double &distancia) const;

    double distanciaA(Posicion &posicion);

    bool estaAbierta();

    bool estaEnPosDelMapa(int &fila, int &columna);

    void settearEstado(bool& estado){
        this->abierta = estado;
    }

    std::vector<char> serializar() override;

    void deserializar(std::vector<char>& informacion) override {}
};

#endif
