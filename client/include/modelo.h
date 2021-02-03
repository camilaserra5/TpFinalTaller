#ifndef _MODELO_H
#define _MODELO_H

#include "ventana.h"
#include "player.h"
#include <map>
#include "objetoJuego.h"
#include "objetosJuego.h"
#include "enemigo.h"
#include <vector>
#include "anunciador.h"
class Modelo {
public:
    Modelo(Ventana *ventana, int idJugador);

    ~Modelo();

    void inicializar(); // viene los datos todos los jugadores?

    void renderizar();

    void renderizarSprite(ObjetoJuego* objeto,int& alturaSprite,int& x,int& y1,double& distanciaObjeto);

    void actualizarJugador(int x, int y, int vida, int angulo, int idArma,
                            bool disparando, int puntaje, int cantVidas,
                            int balas);
    void actualizarEnemigo(int id, int vida, bool disparando,
                            int posx, int posy, int idArma,
                            int anguloJgador, int angulo, int puntaje);

    ObjetoJuego *crearObjeto(Type tipo);

    void actualizarObjeto(int id, Type tipo, int posx, int posy);

    void verificarObjetosEnRangoDeVista();

    std::vector<double>& getZBuffer();

    void verificarEnemigosEnRango();

    void verificarItemsEnRango();

    bool verificarVisibilidadDeObjeto(Posicion& posObjeto);

    Player& getPlayer();

    void terminoPartida(std::vector<int>& rankingJugadores);

    void actualizar();


private:
    Ventana *ventana;
    int idJugador;
    Player* jugador;
    std::map<int, ObjetoJuego *> entidades;
    std::map<int, Enemigo*> enemigos;
    std::vector<double> zbuffer;
    Anunciador anunciador;
    bool partidaTerminada;
    // mapa de entidades dibujables;

};

#endif
