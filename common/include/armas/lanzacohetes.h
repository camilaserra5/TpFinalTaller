#ifndef _LANZA_COHETES_H
#define _LANZA_COHETES_H

#define DISTANCIA_MAX 2000000

#include "arma.h"
#include "items/item.h"

class LanzaCohetes : public Arma, public Item {
public:
    /*
      * crea al lanza cohetes dejandolo valido para uso
      * sus parametros debene estar inicializados
    */
    LanzaCohetes(Posicion &posicion, int id, ConfiguracionPartida& configuracion);
    /*
      * liberara al lanzacohetees con sus recursos
    */
    ~LanzaCohetes();
    /*
      * realiza el ataque a todos los jugadores que se encuentren en el
      * parametro  y devuelve la actualizacion correspondiente
    */
    Actualizacion *atacar(int distancia_a_pared, Jugador *jugador,
                          std::map<int, Jugador *> &jugadores) override;
    /*
      * devuelve true si agarro el arma o false en caso contrario
    */
    bool obtenerBeneficio(Jugador *jugador) override;
    /*
      * devuelve el tipo de arma
    */
    Type getTipo() override;
    /*
      * verifica los jugaores que se encuentran en rango de ataque
    */  
    std::map<int, Jugador *> verificarJugadoresEnRango(Posicion &posicionImpacto,
                                                      std::map<int, Jugador *> &jugadores,Jugador *jugador);

  private:
    ConfiguracionPartida configuracion;
};

#endif
