#include "rayo.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

Rayo::Rayo(double campoDeVision, int ladoCelda, int largoProyector,double anguloBarrido,Posicion& posicion) :
        campoDeVision(campoDeVision), ladoCelda(ladoCelda), tamanio_fila_mapa(tamanio_fila_mapa),
        largoProyector(largoProyector) {
    this->distanciaProyector = (this->largoProyector / 2) / tan(this->campoDeVision / 2);
    this->posXMapa = posicion.pixelesEnX() / ladoCelda;
    this->posYMapa = posicion.pixelesEnY() / ladoCelda;
    this->anguloBarrido = anguloBarrido;
    this->normalizarAngulo();
}

void Rayo::normalizarAngulo() {

  if (this->anguloBarrido < 0){
    this->anguloBarrido = this->anguloBarrido + (4.0 * acos(0.0));
  }else if (this->anguloBarrido > 4 * acos(0.0)){
    this->anguloBarrido = this->anguloBarrido - 4.0 * acos(0.0);
  }
}

void Rayo::verificarCuadrante(const double anguloJugador) {
    if (0.0 <= this->anguloBarrido && this->anguloBarrido <= 2.0 * acos(0.0)) {
        this->abajo = false;
    } else {
        this->abajo = true;
    }
    if (acos(0.0) <= this->anguloBarrido && this->anguloBarrido <= 3.0 * acos(0.0)) {
        this->izquierda = true;
    } else {
        this->izquierda = false;
    }
}

void Rayo::verificarInterseccion(int mapa[][TAMANIO_FILA], double &distancia, Jugador &jugador){
  double distanciaHorizontal = this->ladoCelda * TAMANIO_FILA, distanciaVertical = this->ladoCelda * TAMANIO_COLUMNA;
  this->verificarCuadrante(jugador.getAnguloDeVista());
  if (!this->abajo && !this->izquierda){
    distancia = this->verificarInterseccionPrimerCuadrante(jugador,mapa);
  }else if (!this->abajo && this->izquierda){
    distancia = this->verificarInterseccionSegundoCuadrante(jugador,mapa);
  }else if (this->abajo && this->izquierda){
    distancia = this->verificarInterseccionTercerCuadrante(jugador,mapa);
  }else {
    distancia = this->verificarInterseccionCuartoCuadrante(jugador,mapa);
  }
}

double Rayo::verificarInterseccionPrimerCuadrante(Jugador& jugador,int mapa[][TAMANIO_FILA]){
    double dy,dx,x_h,y_v,tileStep = 1.0,xStep,yStep,distanciaHorizontal = 1000.0,distanciaVertical = 1000.0,x,y;
    double tangente = abs(tan(this->anguloBarrido));
    std::cout << "primer cuad\n";
    /*parametros horizontales*/
    dy = -std::modf (this->posYMapa,&y);
    y = floor(y) - 0.025;
    xStep = 1.0 / tan(this->anguloBarrido);
    if (xStep < 0){
      xStep = -xStep;
    }
    yStep = -tileStep;
    distanciaHorizontal = this->verificarInterseccionHorizontal(jugador,mapa,y,dy,xStep,yStep,tangente);

    /*parametros para vertical*/
    dx = 1.0 - std::modf(this->posXMapa,&x);
    x = floor(x) + 1;
    xStep = tileStep;
    yStep = - tan(this->anguloBarrido);
    if (yStep > 0){
      yStep = -yStep;
    }
    distanciaVertical = this->verificarInterseccionVertical(jugador,mapa,x,dx,xStep,yStep,tangente);
    if (distanciaHorizontal < distanciaVertical){
      this->offset = floor(this->x_h);
      return distanciaHorizontal;
    }else{
      this->offset = floor(this->y_v);
      return distanciaVertical;
    }
}

double Rayo::verificarInterseccionSegundoCuadrante(Jugador& jugador,int mapa[][TAMANIO_FILA]){
    double dy,dx,x_h,y_v,tileStep = 1.0,xStep,yStep,distanciaHorizontal = 1000.0,distanciaVertical = 1000.0,x,y;
    double tangente = abs(tan(this->anguloBarrido));
    std::cout << "segundo cuad\n";

    /*parametros horizontales*/
    dy = -std::modf (this->posYMapa,&y);//creo que deberia ser negativo el diferencial
    y = floor(y) - 0.025;
    xStep = 1.0 / tan(this->anguloBarrido);
    if (xStep > 0.0){
      xStep = -xStep;
    }
    yStep = -tileStep;
    distanciaHorizontal = this->verificarInterseccionHorizontal(jugador,mapa,y,dy,xStep,yStep,tangente);

    /*parametros para vertical*/
    dx = -std::modf(this->posXMapa,&x);
    x = floor(x) - 0.025;
    xStep = -tileStep;
    yStep = -tan(this->anguloBarrido);
    if (yStep > 0.0){
      yStep = -yStep;
    }
    distanciaVertical = this->verificarInterseccionVertical(jugador,mapa,x,dx,xStep,yStep,tangente);
    if (distanciaHorizontal < distanciaVertical){
      this->offset = floor(this->x_h);
      return distanciaHorizontal;
    }else{
      this->offset = floor(this->y_v);
      return distanciaVertical;
    }
}

double Rayo::verificarInterseccionTercerCuadrante(Jugador& jugador,int mapa[][TAMANIO_FILA]){
  double tangente = abs(tan(this->anguloBarrido));
  double dy,dx,x_h,y_v,tileStep = 1.0,xStep,yStep,distanciaHorizontal = 1000.0,distanciaVertical = 1000.0,x,y;
std::cout << "tercer cuad\n";
    /*parametros horizontales*/
    dy = 1.0 - std::modf (this->posYMapa,&y);
    xStep = 1.0 / tan(this->anguloBarrido);
    y = floor(y) + 1.0;
    if (xStep > 0.0){
      xStep = -xStep;
    }
    yStep = tileStep;//pos o neg?? (estaba neg)
    distanciaHorizontal = this->verificarInterseccionHorizontal(jugador,mapa,y,dy,xStep,yStep,tangente);

    /*parametros para vertical*/
    dx = -std::modf(this->posXMapa,&x);// pos o neg???
    x = floor(x) - 0.025;
    xStep = -tileStep;
    yStep = tan(this->anguloBarrido);
    if (yStep < 0.0){
      yStep = -yStep;
    }
    distanciaVertical = this->verificarInterseccionVertical(jugador,mapa,x,dx,xStep,yStep,tangente);
    if (distanciaHorizontal < distanciaVertical){
      this->offset = floor(this->x_h);
      return distanciaHorizontal;
    }else{
      this->offset = floor(this->y_v);
      return distanciaVertical;
    }
}

double Rayo::verificarInterseccionCuartoCuadrante(Jugador& jugador,int mapa[][TAMANIO_FILA]){
    double dy,dx,x_h,y_v,tileStep = 1.0,xStep,yStep,distanciaHorizontal = 1000.0,distanciaVertical = 1000.0,x,y;
    double tangente = abs(tan(this->anguloBarrido));
    std::cout << "cuarto cuad\n";

    /*parametros horizontales*/
    dy = 1.0 - std::modf (this->posYMapa,&y);
    y = floor(y) + 1.0;
    xStep = 1.0 / tan(this->anguloBarrido);
    if (xStep < 0){
      xStep = -xStep;
    }
    yStep = tileStep;
    distanciaHorizontal = this->verificarInterseccionHorizontal(jugador,mapa,y,dy,xStep,yStep,tangente);

    /*parametros para vertical*/
    dx = 1.0 - std::modf(this->posXMapa,&x);
    xStep = tileStep;
    x = floor(x) + 1.0;
    yStep = tan(this->anguloBarrido);
    if (yStep < 0){
      yStep = -yStep;
    }
    distanciaVertical = this->verificarInterseccionVertical(jugador,mapa,x,dx,xStep,yStep,tangente);
    if (distanciaHorizontal < distanciaVertical){
      this->offset = floor(this->x_h);
      return distanciaHorizontal;
    }else{
      this->offset = floor(this->y_v);
      return distanciaVertical;
    }
}

bool Rayo::hallarColision(int mapa[][TAMANIO_FILA],double &interseccionAX,double &interseccionAY,double &xStep,double &yStep){
  bool encontrePared = false;
  int yaMapa = floor(interseccionAY);
  int xaMapa = floor(interseccionAX);

  while (!encontrePared && 0 <= xaMapa && xaMapa < TAMANIO_FILA && 0 <= yaMapa && yaMapa < TAMANIO_COLUMNA) {
      if (mapa[yaMapa][xaMapa] == 1) {
          encontrePared = true;
      }else{
        interseccionAY += yStep;
        interseccionAX += xStep;
        yaMapa = floor(interseccionAY);
        xaMapa = floor(interseccionAX);
      }
  }
  return encontrePared;
}

double Rayo::verificarInterseccionHorizontal(Jugador& jugador,int mapa[][TAMANIO_FILA], double& y,double& dy,double& xStep,double& yStep,double& tg) {
    bool encontrePared = false;
    double x,distancia = this->ladoCelda * TAMANIO_FILA;

    x = this->posXMapa + (dy / tg);
    encontrePared = this->hallarColision(mapa,x,y,xStep,yStep);
    if (encontrePared){
      double aux;
      this->x_h = std::modf(x,&aux) * this->ladoCelda;
      x -= this->posXMapa;
      y -= this->posYMapa;
      double distanciaDistorsionada = this->ladoCelda * sqrt((x * x) + (y * y));
      distancia = distanciaDistorsionada * cos(jugador.getAnguloDeVista() - this->anguloBarrido) + 1;
    }
    return distancia;
}

double Rayo::verificarInterseccionVertical(Jugador& jugador,int mapa[][TAMANIO_FILA], double& x,double& dx,double& xStep,double& yStep,double& tg) {
    bool encontrePared = false;
    double y,distancia = this->ladoCelda * TAMANIO_COLUMNA;
    y = this->posYMapa + (dx * tg);
      encontrePared = this->hallarColision(mapa,x,y,xStep,yStep);
      if (encontrePared){
        double aux;
        this->y_v = std::modf(y,&aux) * this->ladoCelda;
        x -= this->posXMapa;
        y -= this->posYMapa;
        double distanciaDistorsionada = this->ladoCelda * sqrt((x * x) + (y * y));
        distancia = distanciaDistorsionada * cos(jugador.getAnguloDeVista() - this->anguloBarrido) + 1;
      }
      return distancia;
}

int Rayo::getDistanciaProyector() {
    return this->distanciaProyector;
}

int Rayo::getOffset(){
  return this->offset;
}
