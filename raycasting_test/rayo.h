#ifndef RAYO_H
#define RAY0_H
#define TAMANIO_FILA 20
#define TAMANIO_COLUMNA 20

#include "jugador.h"

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
    int tamanio_fila_mapa;

    void verificarCuadrante(const double anguloJugador);

public:
    bool hallarColision(int mapa[][TAMANIO_FILA],double &interseccionAX,double &interseccionAY,double &xa,double &ya);

    Rayo(double campoDeVision, int ladoCelda, int largoProyector,double anguloBarrido);

    bool verificarInterseccion(int mapa[][TAMANIO_FILA], double &distancia, Jugador &jugador);

    bool verificarInterseccionHorizontal(int mapa[][TAMANIO_FILA], double &distancia, Jugador &jugador);

    bool verificarInterseccionVertical(int mapa[][TAMANIO_FILA], double &distancia, Jugador &jugador);

    int getDistanciaProyector();

    void normalizarAngulo();
};

#endif
