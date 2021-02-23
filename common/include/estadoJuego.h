#ifndef _ESTADOJUEGO_H
#define _ESTADOJUEGO_H

#include "map.h"
#include "jugador.h"
#include <map>
#include <string>
#include "armas/arma.h"
#include "iserializable.h"
#include "configuracionPartida.h"

#define CANTIDAD_TOP_JUGADORES 5

class EstadoJuego : public ISerializable {
public:
    /*
      * creara el estado juego dejandolo valido para uso
      * el mapa debe estar inicializado
    */
    EstadoJuego(Map &&mapa, ConfiguracionPartida configuracion);
    /*
      * liberara a la clase con sus recursos
    */
    ~EstadoJuego();
    /*
      * constrcutor por movimiento
    */
    EstadoJuego();
    /*
      * realiza la rotaciona a derecha del juagdor y devuelve la actualiacion
      * correspondiente
    */
    Actualizacion *rotar_a_derecha(int idJugador);
    /*
      * realiza la rotaciona a izquierda del juagdor y devuelve la actualiacion
      * correspondiente
    */
    Actualizacion *rotar_a_izquierda(int idJugador);
    /*
      * mueve al juagdor hacia arriba y devuelves las actualziaciones
      * correspondientes
    */
    std::vector<Actualizacion *> moverse_arriba(int idJugador);
    /*
      * mueve al juagdor hacia abajo y devuelves las actualziaciones
      * correspondientes
    */
    std::vector<Actualizacion *> moverse_abajo(int idJugador);
    /*
      * no mueve al juagdor
    */
    void no_me_muevo(int idJugador);
    /*
      * crea al juagdor y lo agrega al mapa de juagdores
    */
    void agregarJugador(std::string &nombreJugador, int id);
    /*
      * realiza el atauqe del juagdor correspondiente y devuleve las
      * actualizaciones correspondientes
    */
    std::vector<Actualizacion *> realizarAtaque(int idJugador);
    /*
      * serializa la clase devolviendo su informacion
    */
    std::vector<char> serializar() override;
    /*
      * deserialzia la clase y crea las distintas entidadescon sus valores
      * correspondientes
    */
    void deserializar(std::vector<char> &informacion) override;
    /*
      * verifica los jugadores muertos
    */
    void verificarJugadoresMuertos();
    /*
      * desconceta al juagdor, dejandolo con valores invalidos y devuelve
      * la ctualizacion corresponiente
    */
    std::vector<Actualizacion *> desconectarJugador(int idJugador);
    /*
      * verifica si el juagdor esta muerto
    */
    bool estaMuerto(int idJugador);
    /*
      * realiza el movimiento correspondiete del juagdor y devuelve las
      * actualizaciones correspondientes
    */
    std::vector<Actualizacion *> verificarMovimientoJugador(Jugador *jugador, int &posX, int &posY);
    /*
      * abre la puerta y devuelve la actualizacion correspondiente
    */
    Actualizacion *abrirPuerta(int idJugador);
    /*
      * devuelve el mapa de juagdores
    */
    std::map<int, Jugador *> &obtenerJugadores();
    /*
      * devuelve el mapa
    */
    Map &obtenerMapa();
    /*
      * arranca el contador de la partida
    */
    void lanzarContadorTiempoPartida();
    /*
      * actualiza el tiempo que lleba la partida
    */
    void actualizarTiempoPartida();
    /*
      * devuelve true si termino la partida o false en caso contrario
    */
    bool terminoPartida();
    /*
      * le cambia el arma al jugador y devuelve la actualizacion corresponiente
    */
    Actualizacion *cambiarArma(int idJugador);
    /*
      * devuelve el mapa de nuemros
    */
    std::vector<std::vector<int>> GetMapanumerico();
    /*
      * devuelve la posicon del juagdor en base al mapa numerico
    */
    std::vector<int> getPosicionEspecificaJugador(int idJugador);
    /*
      * verifica si en la poscion del juagdor hay items
    */  
    Item *verificarItems(int &posx, int &posy);

    /*
     *Devuelve un vector en el cual estan todas las posiciones de los jugadores enemigos
     *en las posiciones 2N estan las posX, en las 2N+1 las posiciones en Y.
     */
    std::vector<int> getPosicionesEnemigos(int idJugador);
    /*
      * devuelve la posicion del jugador en base a los pixeles
    */
    std::vector<int> getPosicionPixels(int idJugador);
private:
    Map mapa;
    std::map<int, Jugador *> jugadores;
    int contador;
    int jugadoresMuertos = 0;
    ConfiguracionPartida configuracion;
};

#endif
