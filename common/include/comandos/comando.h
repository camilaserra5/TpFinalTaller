#ifndef COMANDO_H
#define COMANDO_H

#include <iostream>
#include <actualizaciones/actualizacion.h>
#include "estadoJuego.h"
#include "iserializable.h"

class Comando : public ISerializable {
public:
    /*
      * creara la clase comando dejandola valida para uso
    */
    Comando(int idJugador);
    /*
      * liberara la clase con sus recursos
    */
    virtual ~Comando() {}
    /*
      * constrcutor pro default
    */
    Comando();
    /*
      * ejecutara el comando correspondiente y devolvera las actualizaciones
      * correspondientes
    */
    virtual std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) = 0;


protected:
    int idJugador;
};

#endif
