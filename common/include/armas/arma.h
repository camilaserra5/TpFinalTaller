#ifndef _ARMA_H
#define _ARMA_H
#define NO_HAY_JUGADOR_CERCANO -1
#define DANIO_MAX 10

#define ID_CUCHILLO 3
#define ID_PISTOLA 4
#define ID_AMETRALLADORA 1
#define ID_LANZACOHETES 5
#define ID_CANION_DE_CADENA 2
#define BALAS_PARA_LANZACOHETES 5

#include <map>
#include <ctime>
#include "posicion.h"
#include "jugador.h"
#include "actualizaciones/actualizacion.h"
#include "configuracionPartida.h"


class Arma {
public:
    /*
      * crearar la clase arma dejandola valida pra uso
      * los parametris debene estar inicializados
    */
    Arma(int distancia_max_atacable, int id, int danio_maximo) :
            distancia_max_atacable(distancia_max_atacable), id(id) {}
    /*
      * libera a la clase con sus recursos
    */
    virtual ~Arma() {}
    /*
      * constructor por default
    */
    Arma();
    /*
      * realiza el ataque si puedo. Devuelve una actualizacion del ataque
    */
    virtual Actualizacion *atacar(int distancia_a_pared, Jugador *jugador,
                                  std::map<int, Jugador *> &jugadores) = 0;

    /*
      * busca el juagdor a menor distancia y devuelve el id
      * sino no hay devuelve -1
    */
    int JugadorAMenorDistancia(Jugador *jugador,
                               std::map<int, Jugador *> &jugadores);
    /*
      * devuelve true si el arma posee el mismo id, sino false
    */
    bool esIgual(Arma *arma);
    /*
      * devuelve el id
    */
    int getId();
    /*
      * devuelve el tipo de arma
    */
    virtual Type getTipo() = 0;

protected:
    int distancia_max_atacable;
    /*
      * devuelve la poscion atacable
    */
    int posicionAtacable(Posicion &atacante, Posicion &otroJugador);

    int id;

};

#endif
