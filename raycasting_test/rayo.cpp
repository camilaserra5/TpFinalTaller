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
        ya = -this->ladoCelda;
    }else{
         interseccionAY = floor(posY/this->ladoCelda) * (this->ladoCelda) - 1;
         ya = this->ladoCelda;
      }

    yaMapa = interseccionAY/this->ladoCelda;
    interseccionAX = posX + (posY-interseccionAY)/tan(this->anguloBarrido + anguloJugador);
    xaMapa = interseccionAX/this->ladoCelda;

    xa = this->ladoCelda / tan(this->anguloBarrido + anguloJugador);

    while (!encontrePared && 0 < xaMapa && xaMapa < TAMANIO_FILA && 0 < yaMapa && yaMapa < TAMANIO_COLUMNA) {
        if (mapa[xaMapa][yaMapa] == 2) {//cheq caoaz esta al revez
            encontrePared = true;
            interseccionAX -= posX;
            interseccionAY -= posY;
            int distanciaDistorsionada = sqrt((interseccionAX * interseccionAX) + (interseccionAY * interseccionAY));
            distancia = distanciaDistorsionada * cos(this->anguloBarrido);
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
    float ya = this->ladoCelda / tan(this->anguloBarrido + anguloJugador);
    float xa = this->verificarCuadranteX(anguloJugador);
    int posX = 4, posY = 2;//lo va a recibir por parametro
    int posXPared = posX * this->ladoCelda, posYPared = posY * this->ladoCelda;
    while (!encontrePared && 0 < posXPared / this->ladoCelda && posXPared / this->ladoCelda < TAMANIO_FILA &&
           0 < posYPared / this->ladoCelda && posYPared / this->ladoCelda < TAMANIO_COLUMNA) {
        if (mapa[posXPared / this->ladoCelda][posYPared / this->ladoCelda] == 2) {
            encontrePared = true;
            posX -= posXPared / this->ladoCelda;//creo que esta mal
            posY -= posYPared / this->ladoCelda;
            int distanciaDistorsionada = 2 * this->ladoCelda + sqrt((posX * posX) + (posY * posY));
            distancia = distanciaDistorsionada * abs(cos(this->anguloBarrido));
            //std::cout << "Para la distancia vertical es: " << distancia <<"\n";
        }
        posXPared = (this->abajo ? floor(posYPared + ya) : ceil(posYPared + ya));
        posYPared += xa;
    }
    return encontrePared;
}

int Rayo::getDistanciaProyector() {
    return this->distanciaProyector;
}

void Rayo::aumentarAnguloBarrido() {
    this->anguloBarrido = this->anguloBarrido + this->anguloPorStripe;
}
