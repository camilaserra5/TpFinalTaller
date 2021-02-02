#ifndef RAYO_H
#define RAY0_H
#define TAMANIO_FILA 20
#define TAMANIO_COLUMNA 20

#include "player.h"

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
    int offset;
    double x_h;
    double y_v;

    void verificarCuadrante(const double anguloJugador);

    double verificarInterseccionPrimerCuadrante(Player& jugador,int mapa[][TAMANIO_FILA]);

    double verificarInterseccionSegundoCuadrante(Player& jugador,int mapa[][TAMANIO_FILA]);

    double verificarInterseccionTercerCuadrante(Player& jugador,int mapa[][TAMANIO_FILA]);

    double verificarInterseccionCuartoCuadrante(Player& jugador,int mapa[][TAMANIO_FILA]);

public:
    bool hallarColision(int mapa[][TAMANIO_FILA], double &interseccionAX, double &interseccionAY, double &xa, double &ya);

    Rayo(double campoDeVision, int ladoCelda, int largoProyector,double anguloBarrido,Posicion& posicion);

    void verificarInterseccion(int mapa[][TAMANIO_FILA], double &distancia, Player &jugador);

    double verificarInterseccionHorizontal(Player& jugador,int mapa[][TAMANIO_FILA], double& y,double& dy,double& xStep,double& yStep,double& tg);

    double verificarInterseccionVertical(Player& jugador,int mapa[][TAMANIO_FILA], double& x,double& dx,double& xStep,double& yStep,double& tg);

    int getDistanciaProyector();

    void normalizarAngulo();

    int getOffset();
};

#endif
