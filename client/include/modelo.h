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
#include "procesadorDeActualizaciones.h"

class Modelo {
public:
    /*
      * creara el modelo dejandolo valido para uso
      * la ventana y la cola protegida deben estar inicializados
      * el id del jugador debe ser valido
    */
    Modelo(Ventana &ventana, int idJugador, ProtectedQueue<Actualizacion *> &updates);
    /*
      * liberara a la clase modelo junto a sus recursos
    */
    ~Modelo();
    /*
      * inicializa la clase modelo
    */
    bool inicializar();
    /*
      * renderiza a los elementos del jugador(arma e informacion), los enemigos
      * y los items
    */
    void renderizar();
    /*
      * rendriza al objeto
    */
    void renderizarObjeto(ObjetoDibujable *objeto, int &alturaSprite, int &x,
                          int &y1, double &distanciaObjeto);
    /*
      * renderiza a todos los objetos que estan en la vista del jugador
    */
    void renderizarObjetosDibujables(std::vector<ObjetoDibujable *> &objetosVisibles);

    /*
      * actualiza los datos iniciales del juagdor
    */
    void actualizarJugador(int x, int y, int vida, int angulo, int idArma,
                           bool disparando, int puntaje, int cantVidas,
                           int balas);
    /*
      * actualiza los datos inicales dle enemigo
    */
    void actualizarEnemigo(int id, int vida, bool disparando,
                           int posx, int posy, int idArma,
                           int anguloJgador, int angulo, int puntaje);
    /*
      * crea al objeto en base al tipo que le llega y lo devuelve
    */
    ObjetoJuego *crearObjeto(Type tipo);
    /*
      * actualiza los datos de  objeto
    */
    void actualizarObjeto(int id, Type tipo, int posx, int posy);
    /*
      * verifica que items o que enemigos estan en la vista del juagdor
    */
    void verificarObjetosEnRangoDeVista();
    /*
      * devuelve el zbuffer
    */
    std::vector<double> &getZBuffer();
    /*
      * verifica los enemigos estan en rango de la vista del jugador y los mete
      * en el vector de objetos visibles
    */
    void verificarEnemigosEnRango(std::vector<ObjetoDibujable *> &objetosVisibles);
    /*
      * verifica los items estan en rango de la vista del jugador y los mete
      * en el vector de objetos visibles
    */
    void verificarItemsEnRango(std::vector<ObjetoDibujable *> &objetosVisibles);
    /*
      *devulve el jugador
    */
    Player &getPlayer();
    /*
      * le avisa a la pantalla de highscore que termino la partida
    */
    void terminoPartida(Ranking &rankingJugadores);
    /*
      * actualiza el zbuffer haciendole clean
    */
    void actualizar();
    /*
      * procesa las actualziaciones que saca de la cola de actualizaciones
    */
    bool procesarActualizaciones();
    /*
      * devuelve el mapa
    */
    Map &obtenerMapa();
    /*
      * actualiza la posicon del juagdor
      */
    void actualizarPosicionJugador(int posX, int posY, float angulo);
    /*
      * actualiza el arma del juagdor
    */
    void actualizarArmaJugador(int idArma);
    /*
      * actualiza el arma a los enemigos
    */
    void actualizarArmaEnemigos(int idArma);
    /*
      * actualiza el estado de ataque del juagdor
    */
    void actualizarEstadoAtaqueJugador(int vida, int idArma, int cant_balas,
                                       int puntaje, int cant_vidas,
                                       bool atacando);
    /*
      * actualiza la vida del enemigo
    */
    void actualizarVidaEnemigo(int id, int vida, int idArma);
    /*
      * saca al item del mapa de objetos
    */
    void sacarItem(int &id);
    /*
      * actualiza el beneificio de objtener un item al juagdor
    */
    void actualizarBeneficioJugador(int vida, int balas, int puntos,
                                    int cant_vidas);
    /*
      * settea el mapa
    */
    void setMapa(Map& mapa);
    /*
      * actualiza la posicion del enemigo
    */  
    void actualizarPosicionEnemigo(int idE,int posX, int posY, float angulo);

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
