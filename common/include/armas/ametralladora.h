#ifndef AMETRALLADORA_H
#define AMETRALLADORA_H
#define DISTANCIA_MAX 2000000
#define TICKS_DISPARO_AMETRALLADORA  10

#include "arma.h"
#include "items/item.h"
#include "actualizaciones/actualizacion.h"

class Ametralladora : public Arma, public Item {
public:
    /*
      * creara la clase ametralladora dejandola valida para uso
      * sus parametros deben estar inicializados
    */
    Ametralladora(Posicion &posicion, int id, ConfiguracionPartida& configuracion);
    /*
      * liberara la clase con sus recursos
    */
    ~Ametralladora();
    /*
      * ataca al jugador mas cercano, restandole su vida y restando la balas del
      * juagdor si no hay solo resta las balas gastadas del jugador devuele
      * la actualizacion si pudo atacar o null sino
    */
    Actualizacion *atacar(int distancia_a_pared, Jugador *jugador,
                          std::map<int, Jugador *> &jugadores) override;
    /*
      * devuleve true si pudo agarrar el arma o false en caso contrario
    */
    bool obtenerBeneficio(Jugador *jugador) override;
    /*
      * si puede atacar realiza el ataque
    */
    Actualizacion *atacarEfectivamente(Jugador *jugador, std::map<int, Jugador *> &jugadores);
    /*
      * devuelve el tipo de arma
    */  
    Type getTipo() override;


private:
    double contador;
    ConfiguracionPartida configuracion;
};

#endif
