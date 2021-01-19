#include "rayo.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

Rayo::Rayo(float campoDeVision, int ladoCelda/*, int tamanio_fila_mapa*/, int largoProyector,float anguloBarrido) :
        campoDeVision(campoDeVision), ladoCelda(ladoCelda), tamanio_fila_mapa(tamanio_fila_mapa),
        largoProyector(largoProyector) {
    this->distanciaProyector = (this->largoProyector / 2) / tan(this->campoDeVision / 2);
    this->anguloBarrido = anguloBarrido;
    this->normalizarAngulo();
}

void Rayo::normalizarAngulo(){

  if (this->anguloBarrido < 0){
    this->anguloBarrido = this->anguloBarrido + (4 * acos(0.0));
  }else if (this->anguloBarrido > 4 * acos(0.0)){
    this->anguloBarrido = this->anguloBarrido - 4 * acos(0.0);
  }
}

void Rayo::verificarCuadranteY(const float anguloJugador) {
    if (0 <= this->anguloBarrido && this->anguloBarrido <= 2 * acos(0.0)) {
        this->abajo = false;
        std::cout << "arriba ";
    } else {
        this->abajo = true;
        std::cout << "abajo ";
    }
}

void Rayo::verificarCuadranteX(const float anguloJugador) {

    if (acos(0.0) <= this->anguloBarrido && this->anguloBarrido <= 3 * acos(0.0)) {
        this->izquierda = true;
        std::cout <<"izquierda\n";
    } else {
        this->izquierda = false;
        std::cout << "derecha\n";
    }
}

bool Rayo::verificarInterseccion(int mapa[][TAMANIO_FILA], float &distancia, Jugador &jugador){
  float distanciaHorizontal = this->ladoCelda * TAMANIO_FILA, distanciaVertical = this->ladoCelda * TAMANIO_COLUMNA;
  this->verificarCuadranteY(jugador.getAnguloDeVista());
  this->verificarCuadranteX(jugador.getAnguloDeVista());
  bool hayInterseccionHorizontal = this->verificarInterseccionHorizontal(mapa,distanciaHorizontal,jugador);
  bool hayInterseccionVertical = this->verificarInterseccionVertical(mapa,distanciaVertical,jugador);
  distancia = (distanciaHorizontal < distanciaVertical? distanciaHorizontal:distanciaVertical);

  return (hayInterseccionVertical || hayInterseccionHorizontal);
}

bool Rayo::verificarInterseccionHorizontal(int mapa[][TAMANIO_FILA], float &distancia, Jugador &jugador) {
    bool encontrePared = false;
    Posicion posJugador = jugador.getPosicion();
    int posX = posJugador.pixelesEnX(), posY = posJugador.pixelesEnY();// en pixels
    float interseccionAX,interseccionAY,xa,ya;// el primer punto de interseccion al que desp se le suma ya y xa
    int xaMapa,yaMapa;

    if (this->abajo){
        interseccionAY = floor(posY/this->ladoCelda) * (this->ladoCelda) + this->ladoCelda;
        ya = this->ladoCelda;
    }else{
         interseccionAY = floor(posY/this->ladoCelda) * (this->ladoCelda) - 1;
         ya = -this->ladoCelda;
      }

    yaMapa = interseccionAY/this->ladoCelda;//posicion en el mapa para accederlo
    interseccionAX = posX + (posY-interseccionAY)/tan(this->anguloBarrido);
    xaMapa = interseccionAX/this->ladoCelda;//posicion en el mapa para accederlo
    xa = floor(this->ladoCelda / tan(this->anguloBarrido));

    if ((this->izquierda && xa > 0) || (!this->izquierda && xa < 0)){
      xa = -xa;
    }

    while (!encontrePared && 0 < xaMapa && xaMapa < TAMANIO_FILA && 0 < yaMapa && yaMapa < TAMANIO_COLUMNA) {
        if (mapa[xaMapa][yaMapa] == 1) {
            encontrePared = true;
            interseccionAX -= posX;
            interseccionAY -= posY;
            int distanciaDistorsionada = sqrt((interseccionAX * interseccionAX) + (interseccionAY * interseccionAY));
            distancia = distanciaDistorsionada * cos(jugador.getAnguloDeVista() - this->anguloBarrido) + 10;

        }
        interseccionAX = interseccionAX + xa;
        interseccionAY += ya;
        yaMapa = interseccionAY/this->ladoCelda;
        xaMapa = interseccionAX/this->ladoCelda;
    }
    return encontrePared;
}

bool Rayo::verificarInterseccionVertical(int mapa[][TAMANIO_FILA], float &distancia, Jugador &jugador) {
    bool encontrePared = false;
    Posicion posJugador = jugador.getPosicion();
    int posX = posJugador.pixelesEnX(), posY = posJugador.pixelesEnY();// en pixels
    float interseccionAX,interseccionAY,xa,ya;// el primer punto de interseccion al que desp se le suma ya y xa
    int xaMapa,yaMapa;


    if (this->izquierda){
        interseccionAX = floor(posX/this->ladoCelda) * (this->ladoCelda) - 1;
        xa = -this->ladoCelda;
    }else{
        interseccionAX = floor(posX/this->ladoCelda) * (this->ladoCelda) + this->ladoCelda;
         xa = this->ladoCelda;
      }

      xaMapa = interseccionAX/this->ladoCelda;
      interseccionAY = posY + (posX-interseccionAX)/tan(this->anguloBarrido);
      yaMapa = floor(interseccionAY/this->ladoCelda);

      ya = this->ladoCelda / tan(this->anguloBarrido);
      if ((this->abajo && ya < 0) || (!this->abajo && ya > 0)){
        ya = -ya;
      }

    while (!encontrePared && 0 < xaMapa && xaMapa < TAMANIO_FILA && 0 < yaMapa && yaMapa < TAMANIO_COLUMNA) {
        if (mapa[xaMapa][yaMapa] == 1) {
            encontrePared = true;
            interseccionAX -= posX;
            interseccionAY -= posY;
            int distanciaDistorsionada = sqrt((interseccionAX * interseccionAX) + (interseccionAY * interseccionAY));
            distancia = distanciaDistorsionada * cos(jugador.getAnguloDeVista() - this->anguloBarrido) + 10;
            //std::cout << "Para la distancia vertical es: " << distancia << "con angulo: " << this->anguloBarrido <<"\n";
        }
        interseccionAY = interseccionAY + ya;
        interseccionAX += xa;
        yaMapa = interseccionAY/this->ladoCelda;
        xaMapa = interseccionAX/this->ladoCelda;
    }
    return encontrePared;
}

int Rayo::getDistanciaProyector() {
    return this->distanciaProyector;
}
