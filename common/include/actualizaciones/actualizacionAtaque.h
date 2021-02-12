#ifndef ACTUALIZACION_ATAQUE_H
#define ACTUALIZACION_ATAQUE_H


#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"
#include "jugador.h"
#include <map>

class ActualizacionAtaque : public Actualizacion {
public:
    ActualizacionAtaque(Jugador* jugador, std::map<int, Jugador*>& jugadoresAtacados);
    ActualizacionAtaque(){}
    ~ActualizacionAtaque();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::ataque); }

private:
    Jugador* jugador;
    std::map<int, Jugador*> jugadoresAtacados;
};

#endif
