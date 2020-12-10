#ifndef COMANDO_H
#define COMANDO_H
#include <iostream>

class Comando{
  public:
    Comando(){}
    virtual ~Comando(){}
    virtual void estrategia() = 0; //deberia devolver una actualizacion en lugar de viod
  private:
    int idJugador;
};

/* comandos que se me ocurren:
-moviemiento
-disparo
-agarrar objetos del piso
*/

#endif
