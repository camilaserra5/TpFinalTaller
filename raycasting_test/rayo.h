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
    double posXMapa;
    double posYMapa;
    double offset;
    double x_h;
    double y_v;

    void verificarCuadrante(const double anguloJugador);

    double verificarInterseccionPrimerCuadrante(Jugador& jugador,int mapa[][TAMANIO_FILA]);

    double verificarInterseccionSegundoCuadrante(Jugador& jugador,int mapa[][TAMANIO_FILA]);

    double verificarInterseccionTercerCuadrante(Jugador& jugador,int mapa[][TAMANIO_FILA]);

    double verificarInterseccionCuartoCuadrante(Jugador& jugador,int mapa[][TAMANIO_FILA]);

public:
    bool hallarColision(int mapa[][TAMANIO_FILA], double &interseccionAX, double &interseccionAY, double &xa, double &ya);

    Rayo(double campoDeVision, int ladoCelda, int largoProyector,double anguloBarrido,Posicion& posicion);

    void verificarInterseccion(int mapa[][TAMANIO_FILA], double &distancia, Jugador &jugador);

    double verificarInterseccionHorizontal(Jugador& jugador,int mapa[][TAMANIO_FILA], double& y,double& dy,double& xStep,double& yStep,double& tg);

    double verificarInterseccionVertical(Jugador& jugador,int mapa[][TAMANIO_FILA], double& x,double& dx,double& xStep,double& yStep,double& tg);

    int getDistanciaProyector();

    void normalizarAngulo();

    double getOffset();
};

#endif
