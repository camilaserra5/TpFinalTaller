#include "rayo.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

int Rayo::verificarCuadranteY(const float anguloJugador){
    float anguloBarrido = anguloJugador;
    if (this->anguloBarrido < 2*acos(0.0) / 6){
      anguloBarrido = anguloJugador - this->anguloBarrido;
    }else{
       anguloBarrido = anguloJugador + this->anguloBarrido;
    }
  if (0 <= anguloBarrido && anguloBarrido <= 2*acos(0.0)){
    this->abajo = false;
    return ladoCelda;
  }else{
    this->abajo = true;
    return -ladoCelda;
  }
}

int Rayo::verificarCuadranteX(const float anguloJugador){
    float anguloBarrido = anguloJugador;
    if (this->anguloBarrido < 2*acos(0.0) / 6){
      anguloBarrido = anguloJugador - this->anguloBarrido;
    }else{
       anguloBarrido = anguloJugador + this->anguloBarrido;
    }
  if (acos(0.0) <= anguloBarrido && anguloBarrido <= 3*acos(0.0)){
    this->izquierda = true;
    return -ladoCelda;
  }else{
    this->izquierda = false;
    return ladoCelda;
  }
}

Rayo::Rayo(float campoDeVision,int ladoCelda,int tamanio_fila_mapa,int largoProyector):
  campoDeVision(campoDeVision),ladoCelda(ladoCelda),tamanio_fila_mapa(tamanio_fila_mapa),
  largoProyector(largoProyector){
    this->distanciaProyector = (this->largoProyector / 2) / tan(this->campoDeVision / 2);
    //this->ladoMapa = this->ladoCelda * this->tamanio_fila_mapa; // lado celda * tamnaio de cada fila
    this->anguloPorStripe =  this->campoDeVision / this->tamanio_fila_mapa;
    this->anguloBarrido = this->anguloPorStripe;
}

bool Rayo::verificarInterseccionHorizontal(int mapa[][TAMANIO_FILA],float& distancia,const float anguloJugador){
  bool encontrePared = false;
  int posX = 4, posY = 2;//lo va a recibir por parametro
  float ya = this->verificarCuadranteY(anguloJugador);
  float xa = this->ladoCelda / tan(this->anguloBarrido);
  int posXPared = posX * this->ladoCelda, posYPared = posY * this->ladoCelda;
  while (!encontrePared && 0 < posXPared/this->ladoCelda && posXPared/this->ladoCelda < TAMANIO_FILA &&  0 < posYPared/this->ladoCelda && posYPared/this->ladoCelda < TAMANIO_COLUMNA){
    if (mapa[posXPared/this->ladoCelda][posYPared/this->ladoCelda] == 2){
      encontrePared = true;
      posX -= posXPared/this->ladoCelda;
      posY -= posYPared/this->ladoCelda;
      int distanciaDistorsionada = 2 * this->ladoCelda + sqrt((posX * posX) + (posY * posY));
      distancia = distanciaDistorsionada * abs(cos(this->anguloBarrido));
      //std::cout << "Para la distancia horizontal es: " << distancia <<"\n";

    }
    posXPared = (this->izquierda? floor(posXPared + xa):ceil(posXPared + xa));
    posYPared += ya;
  }
  return encontrePared;
}

bool Rayo::verificarInterseccionVertical(int mapa[][TAMANIO_FILA],float& distancia,const float anguloJugador){
  bool encontrePared = false;
  float ya = this->ladoCelda / tan(this->anguloBarrido);
  float xa = this->verificarCuadranteX(anguloJugador);
  int posX = 4, posY = 2;//lo va a recibir por parametro
  int posXPared = posX * this->ladoCelda, posYPared = posY * this->ladoCelda;
  while (!encontrePared && 0 < posXPared/this->ladoCelda && posXPared/this->ladoCelda < TAMANIO_FILA &&  0 < posYPared/this->ladoCelda && posYPared/this->ladoCelda < TAMANIO_COLUMNA){
    if (mapa[posXPared/this->ladoCelda][posYPared/this->ladoCelda] == 2){
      encontrePared = true;
      posX -= posXPared/this->ladoCelda;//creo que esta mal
      posY -= posYPared/this->ladoCelda;
      int distanciaDistorsionada = 2 * this->ladoCelda + sqrt((posX * posX) + (posY * posY));
      distancia = distanciaDistorsionada * abs(cos(this->anguloBarrido));
      //std::cout << "Para la distancia vertical es: " << distancia <<"\n";
    }
    posXPared = (this->abajo? floor(posYPared + ya):ceil(posYPared + ya));
    posYPared += xa;
  }
  return encontrePared;
}

int Rayo::getDistanciaProyector(){
  return this->distanciaProyector;
}
void Rayo::aumentarAnguloBarrido(){
  this->anguloBarrido = this->anguloBarrido + this->anguloPorStripe;
}
