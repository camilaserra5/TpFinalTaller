#ifndef COMANDO_H
#define COMANDO_H

#include <iostream>
#include "estadoJuego.h"

class Comando {
public:
    Comando() {}

    virtual ~Comando() {}

    virtual void estrategia(EstadoJuego &estadoJuego) = 0; //deberia devolver una actualizacion en lugar de viod
private:
    int idJugador;
};

/* comandos que se me ocurren:
-moviemiento
-disparo
-agarrar objetos del piso
*/

#endif
