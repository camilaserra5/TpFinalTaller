#ifndef _LANZA_COHETES_H
#define _LANZA_COHETES_H

#define DISTANCIA_MAX 2000000

#include "arma.h"
#include "items/item.h"

class LanzaCohetes : public Arma, public Item {
public:
    LanzaCohetes(Posicion &posicion, int id, ConfiguracionPartida& configuracion);

    ~LanzaCohetes();

    Actualizacion *atacar(int distancia_a_pared, Jugador *jugador,
                          std::map<int, Jugador *> &jugadores) override;

    bool obtenerBeneficio(Jugador *jugador) override;

    Type getTipo() override;

    std::map<int, Jugador *> verificarJugadoresEnRango(Posicion &posicionImpacto,
                                                      std::map<int, Jugador *> &jugadores,Jugador *jugador);

  private:
    ConfiguracionPartida configuracion;
};

#endif
