#include "rayo.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

Rayo::Rayo(double campoDeVision, int ladoCelda/*, int tamanio_fila_mapa*/, int largoProyector,double anguloBarrido) :
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

void Rayo::verificarCuadrante(const double anguloJugador) {
    if (0 <= this->anguloBarrido && this->anguloBarrido <= 2.0 * acos(0.0)) {
        this->abajo = false;
        std::cout << "arriba\n";
    } else {
        this->abajo = true;
        std::cout << "abajo\n";

    }
    if (acos(0.0) <= this->anguloBarrido && this->anguloBarrido <= 3.0 * acos(0.0)) {
        this->izquierda = true;
        std::cout << "izq\n";
    } else {
        this->izquierda = false;
        std::cout << "der\n";

    }
}

bool Rayo::verificarInterseccion(int mapa[][TAMANIO_FILA], double &distancia, Jugador &jugador){
  double distanciaHorizontal = this->ladoCelda * TAMANIO_FILA, distanciaVertical = this->ladoCelda * TAMANIO_COLUMNA;
  this->verificarCuadrante(jugador.getAnguloDeVista());
  bool hayInterseccionHorizontal = this->verificarInterseccionHorizontal(mapa,distanciaHorizontal,jugador);
  bool hayInterseccionVertical = this->verificarInterseccionVertical(mapa,distanciaVertical,jugador);

  distancia = (distanciaHorizontal < distanciaVertical? distanciaHorizontal:distanciaVertical);
  return (hayInterseccionVertical || hayInterseccionHorizontal);
}

bool Rayo::hallarColision(int mapa[][TAMANIO_FILA],double &interseccionAX,double &interseccionAY,double &xa,double &ya){
  bool encontrePared = false;
  int yaMapa = floor(interseccionAY/this->ladoCelda);
  int xaMapa = floor(interseccionAX/this->ladoCelda);


  while (!encontrePared && 0 < xaMapa && xaMapa < TAMANIO_FILA && 0 < yaMapa && yaMapa < TAMANIO_COLUMNA) {
//    std::cout << "avance xa: " << xa << " y: " << ya << "\n";

      if (mapa[xaMapa][yaMapa] == 1) {
//          std::cout << "llego en xa: " << xaMapa << " y: " << yaMapa << "\n";
          encontrePared = true;
      }else{
        interseccionAX += xa;
        interseccionAY += ya;
        yaMapa = floor(interseccionAY/this->ladoCelda);
        xaMapa = floor(interseccionAX/this->ladoCelda);
      }
  }
  return encontrePared;
}

bool Rayo::verificarInterseccionHorizontal(int mapa[][TAMANIO_FILA], double &distancia, Jugador &jugador) {
  std::cout << "llamo a hallar hor con angulo:" << this->anguloBarrido <<" \n";

    bool encontrePared = false;
    Posicion posJugador = jugador.getPosicion();
    int posX = posJugador.pixelesEnX(), posY = posJugador.pixelesEnY();// en pixels
    double interseccionAX,interseccionAY,xa,ya,dy;// el primer punto de interseccion al que desp se le suma ya y xa

    if (this->abajo){
        dy = posY - (ceil(posY/this->ladoCelda) * this->ladoCelda);
        ya = this->ladoCelda;
    }else{
        dy = posY - (floor(posY/this->ladoCelda) * this->ladoCelda) - 1;
         ya = -this->ladoCelda;
      }
    interseccionAY = posY + dy;
    interseccionAX = posX + dy/tan(this->anguloBarrido);
    std::cout << "primer punto de interseccion para horizontal :" << interseccionAX/this->ladoCelda << " y: " << interseccionAY/this->ladoCelda << "\n";
    xa = this->ladoCelda / tan(this->anguloBarrido);

    if ((this->izquierda && xa > 0) || (!this->izquierda && xa < 0)){
      xa = xa * (-1);
    }
// /    xa = xa + (xa < this->ladoCelda? this->ladoCelda: - this->ladoCelda);
    encontrePared = this->hallarColision(mapa,interseccionAX,interseccionAY,xa,ya);
    if (encontrePared){
      //calculoDistancia
      interseccionAX -= posX;
      interseccionAY -= posY;
      int distanciaDistorsionada = sqrt((interseccionAX * interseccionAX) + (interseccionAY * interseccionAY));
      distancia = distanciaDistorsionada * cos(jugador.getAnguloDeVista() - this->anguloBarrido) + 1;
    }

    return encontrePared;
}

bool Rayo::verificarInterseccionVertical(int mapa[][TAMANIO_FILA], double &distancia, Jugador &jugador) {
    bool encontrePared = false;
    Posicion posJugador = jugador.getPosicion();
    int posX = posJugador.pixelesEnX(), posY = posJugador.pixelesEnY();// en pixels
    double interseccionAX,interseccionAY,xa,ya,dx;// el primer punto de interseccion al que desp se le suma ya y xa

    if (this->izquierda){
        dx = posX - floor(posX/this->ladoCelda) * this->ladoCelda - 1;
        xa = -this->ladoCelda;
    }else{
        dx = posX - ceil(posX/this->ladoCelda) * this->ladoCelda;
        xa = this->ladoCelda;
      }
      interseccionAX = posX + dx;
      interseccionAY = posY + dx/tan(this->anguloBarrido);



      ya = this->ladoCelda / tan(this->anguloBarrido);

      if ((this->abajo && ya < 0) || (!this->abajo && ya > 0)){
        ya = (-1) * ya;
      }
  //    ya = ya + (ya < this->ladoCelda? this->ladoCelda: - this->ladoCelda);

    std::cout << "llamo a hallar vertical con tan(angulo):" << tan(this->anguloBarrido) <<"\n";
    std::cout << "primer punto de interseccion para vertical :" << interseccionAX/this->ladoCelda << " y: " << interseccionAY/this->ladoCelda << "\n";

      encontrePared = this->hallarColision(mapa,interseccionAX,interseccionAY,xa,ya);
      if (encontrePared){
        //calculoDistancia
        interseccionAX -= posX;
        interseccionAY -= posY;
        int distanciaDistorsionada = sqrt((interseccionAX * interseccionAX) + (interseccionAY * interseccionAY));
        distancia = distanciaDistorsionada * cos(jugador.getAnguloDeVista() - this->anguloBarrido) + 1;
      }

    return encontrePared;
}

int Rayo::getDistanciaProyector() {
    return this->distanciaProyector;
}
