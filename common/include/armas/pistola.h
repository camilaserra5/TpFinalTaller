#ifndef _PISTOLA_H
#define _PISTOLA_H

#include "armas/arma.h"


class Pistola : public Arma {

public:
    /*
      * creara el arma dejandola valida para uso
      * sus parametros debne estar validos
    */
    Pistola(ConfiguracionPartida& configuracion);
    /*
      * liberara la memoriacon sus recursos
    */
    ~Pistola();
    /*
      * realiza el ataque al jugador mas cercano y devuelve la actualizacion
      * correspondiente
    */
    Actualizacion *atacar(int distancia_a_pared, Jugador *jugador,
                          std::map<int, Jugador *> &jugadores) override;
    /*
      * devuelve el tipo de arma
    */
    Type getTipo() override;
    /*
      * constructor por default
    */  
    Pistola() {}

private:

    ConfiguracionPartida configuracion;
};

#endif
