#ifndef _MODELO_H
#define _MODELO_H

#include "ventana.h"
#include "player.h"
#include <map>
#include "objetoJuego.h"
#include "objetosJuego.h"
#include "enemigo.h"

class Modelo {
public:
    Modelo(Ventana *ventana, int idJugador);

    ~Modelo();

    void inicializar(); // viene los datos todos los jugadores?
    void renderizar();

    void actualizarJugador(int x, int y, int vida, int angulo, int id, int idArma);

    ObjetoJuego *crearObjeto(Type tipo);

    void actualizarObjeto(int id, Type tipo, int posx, int posy);

private:
    Ventana *ventana;
    int idJugador;
    Player* jugador;
    std::map<int, ObjetoJuego *> entidades;
    std::vector<Enemigo*> enemigos;
    int x;
    // mapa de entidades dibujables;

};

#endif
