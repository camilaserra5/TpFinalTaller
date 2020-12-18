#include "rayo.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

//posy,posx en pixeles


void Rayo::verificarCuadranteY(const float anguloJugador) {
    float anguloBarrido = anguloJugador;
    if (this->anguloBarrido < 2 * acos(0.0) / 6) {
        anguloBarrido = anguloJugador - this->anguloBarrido;
    } else {
        anguloBarrido = anguloJugador + this->anguloBarrido;
    }
    if (0 <= anguloBarrido && anguloBarrido <= 2 * acos(0.0)) {
        this->abajo = false;
    } else {
        this->abajo = true;
    }
}

void Rayo::verificarCuadranteX(const float anguloJugador) {
    float anguloBarrido = anguloJugador;
    if (this->anguloBarrido < 2 * acos(0.0) / 6) {
        anguloBarrido = anguloJugador - this->anguloBarrido;
    } else {
        anguloBarrido = anguloJugador + this->anguloBarrido;
    }
    if (acos(0.0) <= anguloBarrido && anguloBarrido <= 3 * acos(0.0)) {
        this->izquierda = true;
    } else {
        this->izquierda = false;
    }
}

Rayo::Rayo(float campoDeVision, int ladoCelda, int tamanio_fila_mapa, int largoProyector) :
        campoDeVision(campoDeVision), ladoCelda(ladoCelda), tamanio_fila_mapa(tamanio_fila_mapa),
        largoProyector(largoProyector) {
    this->distanciaProyector = (this->largoProyector / 2) / tan(this->campoDeVision / 2);
    //this->ladoMapa = this->ladoCelda * this->tamanio_fila_mapa; // lado celda * tamnaio de cada fila
    this->anguloPorStripe = this->campoDeVision / this->tamanio_fila_mapa;
    this->anguloBarrido = this->anguloPorStripe;
}

bool Rayo::verificarInterseccionHorizontal(int mapa[][TAMANIO_FILA], float &distancia, const float anguloJugador) {
    bool encontrePared = false;
    int posX = 120, posY = 100;// en pixels
    float interseccionAX,interseccionAY,xa,ya;// el primer punto de interseccion al que desp se le suma ya y xa
    int xaMapa,yaMapa;

    //pasar la posicion a metros

    this->verificarCuadranteY(anguloJugador);

    if (this->abajo){
        interseccionAY = floor(posY/this->ladoCelda) * (this->ladoCelda) + this->ladoCelda;
        ya = this->ladoCelda;
    }else{
         interseccionAY = ceil(posY/this->ladoCelda) * (this->ladoCelda) - 1;
         ya = -this->ladoCelda;
      }

    yaMapa = interseccionAY/this->ladoCelda;
    interseccionAX = posX + (posY-interseccionAY)/tan(this->anguloBarrido);
    xaMapa = interseccionAX/this->ladoCelda;
    xa = this->ladoCelda / tan(this->anguloBarrido);

    xaMapa --;//cheq
    yaMapa--;
    while (!encontrePared && 0 < xaMapa && xaMapa < TAMANIO_FILA && 0 < yaMapa && yaMapa < TAMANIO_COLUMNA) {
        if (mapa[xaMapa][yaMapa] == 1) {//cheq caoaz esta al revez
          std::cout << "posiciones h: " << xaMapa <<" y " << yaMapa << "\n";

            encontrePared = true;
            interseccionAX -= posX;
            interseccionAY -= posY;
            int distanciaDistorsionada = sqrt((interseccionAX * interseccionAX) + (interseccionAY * interseccionAY));
            distancia = distanciaDistorsionada * cos(this->anguloBarrido) + 3;
            std::cout << "Para la distancia horizontal es: " << distancia  << "con angulo: " << this->anguloBarrido <<"\n";

        }
        interseccionAX = floor(interseccionAX + xa);
        interseccionAY += ya;
        yaMapa = interseccionAY/this->ladoCelda;
        xaMapa = interseccionAX/this->ladoCelda;
    }
    return encontrePared;
}

bool Rayo::verificarInterseccionVertical(int mapa[][TAMANIO_FILA], float &distancia, const float anguloJugador) {
    bool encontrePared = false;
    int posX = 120, posY = 100;// en pixels
    float interseccionAX,interseccionAY,xa,ya;// el primer punto de interseccion al que desp se le suma ya y xa
    int xaMapa,yaMapa;

    this->verificarCuadranteX(anguloJugador);

    if (this->izquierda){
        interseccionAX = floor(posX/this->ladoCelda) * (this->ladoCelda) + this->ladoCelda;
        xa = -this->ladoCelda;
    }else{
         interseccionAX = ceil(posX/this->ladoCelda) * (this->ladoCelda) - 1;
         xa = this->ladoCelda;
      }

      xaMapa = interseccionAX/this->ladoCelda;
      interseccionAY = posY + (posX-interseccionAX)/tan(this->anguloBarrido);
      yaMapa = interseccionAY/this->ladoCelda;

      ya = this->ladoCelda / tan(this->anguloBarrido);
      xaMapa --;
      yaMapa--;
    while (!encontrePared && 0 < xaMapa && xaMapa < TAMANIO_FILA && 0 < yaMapa && yaMapa < TAMANIO_COLUMNA) {
        if (mapa[xaMapa][yaMapa] == 1) {
          std::cout << "posiciones: " << xaMapa <<" y " << yaMapa << "\n";

            encontrePared = true;
            interseccionAX -= posX;
            interseccionAY -= posY;
            int distanciaDistorsionada = sqrt((interseccionAX * interseccionAX) + (interseccionAY * interseccionAY));
            distancia = distanciaDistorsionada * cos(this->anguloBarrido) + 3;
            std::cout << "Para la distancia vertical es: " << distancia << "con angulo: " << this->anguloBarrido <<"\n";
        }
        interseccionAY = floor(interseccionAY + ya);
        interseccionAX += xa;
        yaMapa = interseccionAY/this->ladoCelda;
        xaMapa = interseccionAX/this->ladoCelda;
    }
    return encontrePared;
}

int Rayo::getDistanciaProyector() {
    return this->distanciaProyector;
}

void Rayo::aumentarAnguloBarrido() {
    this->anguloBarrido = this->anguloBarrido + this->anguloPorStripe;
    this->anguloBarrido = fmodf(this->anguloBarrido,4 * acos(0.0));
    if (this->anguloBarrido < 0 ) this->anguloBarrido += 4 * acos(0.0);
}
