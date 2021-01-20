#ifndef RAYO_H
#define RAY0_H
#define TAMANIO_FILA 20
#define TAMANIO_COLUMNA 20

#include "jugador.h"

class Rayo {
private:
    bool abajo = false;
    bool izquierda = false;
    float xa;
    float ya;
    float campoDeVision;
    float anguloBarrido;
    int largoProyector;
    int alturaProyector;
    int distanciaProyector;
    float anguloPorStripe;
    int ladoCelda;
    int ladoMapa;
    int tamanio_fila_mapa;

    void verificarCuadranteX(const float anguloJugador);

    void verificarCuadranteY(const float anguloJugador);

    bool hallarColision(int mapa[][TAMANIO_FILA],float &interseccionAX,float &interseccionAY,float &xa,float &ya);

public:
    Rayo(float campoDeVision, int ladoCelda, /*int tamanio_fila_mapa, */int largoProyector,float anguloBarrido);

    bool verificarInterseccion(int mapa[][TAMANIO_FILA], float &distancia, Jugador &jugador);

    bool verificarInterseccionHorizontal(int mapa[][TAMANIO_FILA], float &distancia, Jugador &jugador);

    bool verificarInterseccionVertical(int mapa[][TAMANIO_FILA], float &distancia, Jugador &jugador);

    int getDistanciaProyector();

    void normalizarAngulo();
};

#endif
