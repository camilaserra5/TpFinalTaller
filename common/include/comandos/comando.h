#ifndef COMANDO_H
#define COMANDO_H

#include <iostream>
#include "estadoJuego.h"
#include "iserializable.h"

class Comando : public ISerializable{
public:
    Comando() {}

    virtual ~Comando() {}

    virtual void ejecutar(EstadoJuego &estadoJuego) = 0; //deberia devolver una actualizacion en lugar de viod

  //  std::stringstream serializar(){}


private:
    int idJugador;
};

/* comandos que se me ocurren:
-moviemiento
-disparo
-agarrar objetos del piso
*/

#endif
