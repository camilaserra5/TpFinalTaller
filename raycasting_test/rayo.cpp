#include "rayo.h"
#include <math.h>
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
    this->anguloBarrido = anguloPorStripe;
}

bool Rayo::verificarInterseccionHorizontal(int mapa[][TAMANIO_FILA],float& distancia,const float anguloJugador){
  bool encontrePared = false;
  int posX = 4, posY = 2;//lo va a recibir por parametro
  int posXPared = posX * this->ladoCelda, posYPared = posY * this->ladoCelda;
  float ya = this->verificarCuadranteY(anguloJugador);
  float xa = this->ladoCelda / tan(this->anguloPorStripe);
  while (!encontrePared && 0 < posX && posX < TAMANIO_FILA &&  0 < posY && posY < TAMANIO_COLUMNA){
    if (mapa[posXPared/this->ladoCelda][posYPared/this->ladoCelda] == 2){
      encontrePared = true;
      std::cout << "Para la interseccion horizontal x: " << posXPared << " y: "<< posYPared <<"\n";
      posX -= posXPared/this->ladoCelda;
      posY -= posYPared/this->ladoCelda;
      distancia = 2 * this->ladoCelda+ sqrt((posX * posX) + (posY * posY));
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
  int posXPared = posX, posYPared = posY;
  while (!encontrePared && 0 < posX && posX < TAMANIO_FILA &&  0 < posY && posY < TAMANIO_COLUMNA){
    if (mapa[posXPared % 320][posYPared % 320] == 2){
      encontrePared = true;
      std::cout << "Para la interseccion vertical x: " << posX << " y: "<< posY <<"\n";
      posX -= posXPared;//creo que esta mal
      posY -= posYPared;
      distancia = 2 * this->ladoCelda + sqrt((posX * posX) + (posY * posY));
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
  this->anguloBarrido += this->anguloPorStripe;
  std::cout << "el angulo barrido es: " << this->anguloBarrido<< "\n";
}
