#ifndef _ANUNCIADOR_H
#define _ANUNCIADOR_H

#include "player.h"
#include "enemigo.h"
#include <vector>
#include <map>
#include "ventana.h"
#include "label.h"

class Anunciador {
public:
    Anunciador(Ventana &ventana);

    void settearInformacion(Player *jugador, std::map<int, Enemigo *> &enemigos);

    void settearGanadores(std::vector<int> &ganadores);

    void renderizar();

    ~Anunciador();

private:
    std::map<int, Enemigo *> enemigos;
    Player *jugador;
    std::vector<Label> ganadores;
    Ventana &ventana;
    bool mostrar;
};

#endif
