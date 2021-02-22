#ifndef _JUGADOR_H
#define _JUGADOR_H

#include <vector>
#include <string>
#include "posicion.h"
#include "logro.h"
#include <map>
#include "iserializable.h"
#include "configuracionPartida.h"

class Actualizacion;
class Arma;

class Jugador : public ISerializable {
public:
    /*
      * creara al juagdor dejandolo valido para uso
      * sus parametros deben ser validos y estar inicalizados
    */
    Jugador(std::string &nombre, int &id, Posicion &posicion, ConfiguracionPartida& configuracion);
    /*
      * libera la clase con sus recursos
    */
    ~Jugador();
    /*
      * constructor por default
    */
    Jugador();
    /*
      * devuelve el nombre del juagdor
    */
    std::string obtenerNombre();
    /*
      * mueve el juagdor a la posico correspoiente
    */
    void moverse(int posx, int posy);
    /*
      * le cambia el sentido al juagdor
    */
    void rotar(int sentido);
    /*
      * actualiza la vida del juagdor
    */
    void actualizar_vida(int &vidaActualizada);
    /*
      * agregar item
    */
    void agregar_item();
    /*
      * agrega un arma al vector de armas
    */
    void agregar_arma(Arma *arma);
    /*
      * devuelve la cantidad de balas
    */
    int cantidad_balas();
    /*
      * devuelve los puntos de vidas
    */
    int puntos_de_vida();
    /*
      * mata al juagdor
    */
    void morir();
    /*
      * agrega balas al juagdor
    */
    void agregar_balas(int &balas);
    /*
      * devuelve su poscion en x
    */
    int posEnX();
    /*
      * devuelva su poscion en y
    */
    int posEnY();
    /*
      * devuuelve su id
    */
    int getId();
    /*
      * le setea una nueva posicon
    */
    void setPosicion(Posicion &posicion);
    /*
      * devuelve su posicon actual
    */
    Posicion &getPosicion();
    /*
      * de vuleve el arma atcual
    */
    Arma *getArma();
    /*
      * devuelve el angulo de vista
    */
    float getAnguloDeVista();
    /*
      * actualiza el arma del juagdor
    */
    void actualizarArma();
    /*
      * devuelve true si tiene llaves
    */
    bool tengollave();
    /*
      * usa la llave
    */
    void usarLlave();
    /*
      * devuelve true si la vida es menor que cero
    */
    bool estaMuerto();
    /*
      * devuelve true si posee esa arma o false sino
    */
    bool poseeArma(Arma *arma);
    /*
      * agarra la llave
    */
    void agarrarLlave();
    /*
      * suma puntos al juagdor
    */
    void sumarPuntos(int puntos);
    /*
      * gasta balas del juagdor
    */
    void gastarBalas(int cantidadDeBalas);
    /*
      * devuelve el logro dle juagdor
    */
    Logro &obtenerLogro();
    /*
      * agrega enemigos matados
    */
    void aniadirEnemigosMatados(int jugadoresMatados);
    /*
      * devuelve si esta esta disparando
    */
    bool estaDisparando();
    /*
      * actualiza la cant de vidas del juagdor y settea en 100 la vida
    */
    void actualizarNuevaVida();
    /*
      * devuelve la cantidad de vidas
    */
    int cant_de_vida();
    /*
      * devuelve el punatej total
    */
    int obtenerPuntosTotales();
    /*
      * deja de disparara
    */
    void dejarDeDisparar();
    /*
      * realiza el ataque
    */
    void atacar();
    /*
      * serializa la clase y devuelve la inforacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializa la clase cargando los valores previos
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * cambia el arma y devuelve la actualziacion correspondiente
    */  
    Actualizacion *cambiarArma();

private:
    Posicion posicion;
    int id;
    std::string nombre;
    int vida;
    int vidaMax;
    std::map<int, Arma *> armas;
    int balas;
    float velocidadDeRotacion;
    int armaActual;
    int llaves;
    int cantidad_vidas;
    Logro logro;
    bool disparando;
};

#endif
