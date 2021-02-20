#ifndef _MODELO_H
#define _MODELO_H

#include "ventana.h"
#include "player.h"
#include <map>
#include "objetoJuego.h"
#include "objetosJuego.h"
#include "enemigo.h"
#include <vector>
#include "highscoreWindow.h"
#include "actualizaciones/actualizacion.h"
#include "protected_queue.h"

class Modelo {
public:
    Modelo(Ventana &ventana, int idJugador, ProtectedQueue<Actualizacion *> &updates);

    ~Modelo();

    bool inicializar(); // viene los datos todos los jugadores?

    void renderizar();

    void renderizarObjeto(ObjetoDibujable *objeto, int &alturaSprite, int &x,
                          int &y1, double &distanciaObjeto);

    void renderizarObjetosDibujables(std::vector<ObjetoDibujable *> &objetosVisibles);


    //  void renderizarObjeto(Enemigo* enemigo,int& alturaSprite,int& x,int& y1,double& distanciaEnemigo);

    void actualizarJugador(int x, int y, int vida, int angulo, int idArma,
                           bool disparando, int puntaje, int cantVidas,
                           int balas);

    void actualizarEnemigo(int id, int vida, bool disparando,
                           int posx, int posy, int idArma,
                           int anguloJgador, int angulo, int puntaje);

    ObjetoJuego *crearObjeto(Type tipo);

    void actualizarObjeto(int id, Type tipo, int posx, int posy);

    void verificarObjetosEnRangoDeVista();

    std::vector<double> &getZBuffer();

    void verificarEnemigosEnRango(std::vector<ObjetoDibujable *> &objetosVisibles);

    void verificarItemsEnRango(std::vector<ObjetoDibujable *> &objetosVisibles);

    Player &getPlayer();

    void terminoPartida(Ranking &rankingJugadores);

    void actualizar();

    bool procesarActualizaciones();

    Map &obtenerMapa();

    void actualizarPosicionJugador(int posX, int posY, float angulo);

    void actualizarArmaJugador(int idArma);

    void actualizarArmaEnemigos(int idArma);

    void actualizarEstadoAtaqueJugador(int vida, int idArma, int cant_balas,
                                       int puntaje, int cant_vidas,
                                       bool atacando);

    void actualizarVidaEnemigo(int id, int vida, int idArma);

    void sacarItem(int &id);

    void actualizarBeneficioJugador(int vida, int balas, int puntos,
                                    int cant_vidas);

private:
    Ventana &ventana;
    int idJugador;
    Player *jugador;
    Map mapa;
    std::map<int, ObjetoJuego *> entidades;
    std::map<int, Enemigo *> enemigos;
    std::vector<double> zbuffer;
    HighscoreWindow anunciador;
    bool partidaTerminada;
    ProtectedQueue<Actualizacion *> &updates;

    bool verificarVisibilidadDeObjeto(Posicion &posObjeto);
    // mapa de entidades dibujables;

};


#endif
