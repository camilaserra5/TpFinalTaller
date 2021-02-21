#ifndef _JUGADOR_H
#define _JUGADOR_H

#include <vector>
#include <string>
#include "posicion.h"
#include "logro.h"
#include <map>
#include "iserializable.h"

class Actualizacion;


class Arma;

class Jugador : public ISerializable {
public:
    Jugador(std::string &nombre, int &id, Posicion &posicion,float vidaMax, float vRotacion, int cantBalasInicial);

    ~Jugador();

    Jugador();

    std::string obtenerNombre();

    void moverse(int posx, int posy);

    void rotar(int sentido);

    void actualizar_vida(int &vidaActualizada);

    void agregar_item();

    void agregar_arma(Arma *arma);

    int cantidad_balas();

    int puntos_de_vida();

    void morir();

    void agregar_balas(int &balas);

    int posEnX();

    int posEnY();

    int getId();

    void setPosicion(Posicion &posicion);

    Posicion &getPosicion();

    Arma *getArma();

    float getAnguloDeVista();

    void actualizarArma();

    //void setAnguloDeVista(float anguloJugador){this->angulo = anguloJugador; }

    bool tengollave();

    void usarLlave();

    bool estaMuerto();

    bool poseeArma(Arma *arma);

    void agarrarLlave();

    void sumarPuntos(int puntos);

    void gastarBalas(int cantidadDeBalas);

    Logro &obtenerLogro();

    void aniadirEnemigosMatados(int jugadoresMatados);

    bool estaDisparando();

    void actualizarNuevaVida();

    int cant_de_vida();

    int obtenerPuntosTotales();

    void dejarDeDisparar();

    void atacar();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    Actualizacion *cambiarArma();

private:
    Posicion posicion;
    int id;
    std::string nombre;
    int vida;
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
