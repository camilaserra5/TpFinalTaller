#ifndef __PUERTA__H
#define __PUERTA__H

#include "posicion.h"
#include "iserializable.h"

class Puerta : public ISerializable {
private:
    bool abierta;
    bool necesitaLlave;
    Posicion posicion;
    int fila;
    int columna;
    //contador para detectar el cierre de puertas
public:
    /*
      * Creara la clase puerta dejandola avlida para uso
    */
    Puerta(bool necesitaLlave, Posicion posicion, int fila, int columna,
            bool abierta) : abierta(abierta),
                            necesitaLlave(necesitaLlave),
                            posicion(posicion),
                            fila(fila), columna(columna) {}
    /*
      * constructor por default
    */
    Puerta() {}
    /*
      * liberara la clase
    */
    ~Puerta() {}
    /*
      * abre la puerta
    */
    void abrir();
    /*
      * cierra la puerta
    */
    void cerrar();
    /*
      * devuelve tue si puede ser abierta
    */
    bool puedeSerAbierta(bool jugadorTieneLlave, double &distancia) const;
    /*
      * devuelve la distacia a la posicion que le llega
    */
    double distanciaA(Posicion &posicion);
    /*
      * deuvlve true si esta bierta
    */
    bool estaAbierta();
    /*
      * devuelve true si se encuentra en esa poscion del mapa
    */
    bool estaEnPosDelMapa(int &fila, int &columna);
    /*
      * settea el estado de la puerta
    */
    void settearEstado(bool &estado) {
        this->abierta = estado;
    }
    /*
      * serializa la clase devolviendo la informacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializa la clase dejandola en sus valores previos
    */  
    void deserializar(std::vector<char> &informacion) override {}
};

#endif
