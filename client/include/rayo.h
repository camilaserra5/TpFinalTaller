#ifndef RAYO_H
#define RAY0_H

#include "player.h"
#include "map.h"

class Rayo {
private:
    bool abajo = false;
    bool izquierda = false;
    double xa;
    double ya;
    double campoDeVision;
    double anguloBarrido;
    int largoProyector;
    int alturaProyector;
    int distanciaProyector;
    double anguloPorStripe;
    int ladoCelda;
    int ladoMapa;
    float posXMapa;
    float posYMapa;
    int offset;
    double x_h;
    double y_v;
    int tipoDePared = 0;

    /*
      * verifica el tipo de cuadrante en el que esta el angulo del jugador
    */
    void verificarCuadrante(const double anguloJugador);

    /*
      * verificar la interseccion del primer cuadrante
    */
    double verificarInterseccionPrimerCuadrante(Player &jugador, Map &mapa);

    /*
      * verifica la interseecion del segundo cuadrante
    */
    double verificarInterseccionSegundoCuadrante(Player &jugador, Map &mapa);

    /*
      * verifica la interseccion del tercer cuadrante
    */
    double verificarInterseccionTercerCuadrante(Player &jugador, Map &mapa);

    /*
      * verifica la interseccion del cuarto cuadrante
    */
    double verificarInterseccionCuartoCuadrante(Player &jugador, Map &mapa);

public:

    bool hallarColision(Map &mapa, double &interseccionAX, double &interseccionAY, double &xa, double &ya);

    Rayo(double campoDeVision, int ladoCelda, int largoProyector, double anguloBarrido, Posicion &posicion);

    void verificarInterseccion(Map &mapa, double &distancia, Player &jugador);

    double
    verificarInterseccionHorizontal(Player &jugador, Map &mapa, double &y, double &dy, double &xStep, double &yStep,
                                    double &tg);

    double
    verificarInterseccionVertical(Player &jugador, Map &mapa, double &x, double &dx, double &xStep, double &yStep,
                                  double &tg);

    int getDistanciaProyector();

    void normalizarAngulo();

    int getOffset();

    int &getTipoPared();

};

#endif
