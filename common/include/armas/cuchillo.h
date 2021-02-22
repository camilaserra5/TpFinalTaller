#ifndef _CUCHILLO_H
#define _CUCHILLO_H

#include "arma.h"

class Cuchillo : public Arma {
public:
    /*
      * creara la clase cuchillo dejandola valida para uso
    */
    Cuchillo(ConfiguracionPartida& configuracion);
    /*
      * liberara al cuchillo con sus recursos
    */
    ~Cuchillo();
    /*
      * constructor por default
    */
    Cuchillo();
    /*
      * realiza el ataque al jugador mas cercano si puede y devuelve la
      * la ctualizacion correspondiente
    */
    Actualizacion *atacar(int distancia_a_pared, Jugador *jugador,
                          std::map<int, Jugador *> &jugadores) override;
    /*
      * devuelve el tipo de arma
    */  
    Type getTipo() override;

private:
  ConfiguracionPartida configuracion;
};

#endif
