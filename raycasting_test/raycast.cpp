#include <iostream>
#include <math.h>
#include "../common_src/include/map.h"
#include "../common_src/include/map_translator.h"
#include "rayo.h"
#define TAMANIO_FILA 320
#define TAMANIO_COLUMNA 320
#define LADO_CELDA 64
#define LARGO_PROYECTOR 320
#define ANCHO_PROYECTOR 20

void llenar_mapa(int mapa[TAMANIO_FILA][TAMANIO_COLUMNA]){
  for (int i = 0; i < TAMANIO_FILA;i++){
    for (int j = 0; j < TAMANIO_COLUMNA; j++){
      mapa[i][j] = 2;
    }
  }
  mapa[4][0] = 0;
  mapa[4][1] = 0;
  mapa[4][2] = 0;
  mapa[4][3] = 0;
  mapa[4][4] = 0;
  mapa[4][5] = 0;
  mapa[4][6] = 0;
  mapa[4][7] = 0;
  mapa[3][2] = 0;
  mapa[3][2] = 0;
  mapa[3][2] = 0;
  mapa[3][2] = 0;
  mapa[5][2] = 0;
  mapa[5][3] = 0;
  mapa[5][4] = 0;
  mapa[5][5] = 0;
  mapa[5][6] = 0;
  mapa[5][7] = 0;
  mapa[3][3] = 0;
  mapa[3][3] = 0;
  mapa[3][3] = 0;
  mapa[3][3] = 0;
}

int main (){

  int mapa[TAMANIO_FILA][TAMANIO_COLUMNA];
  llenar_mapa(mapa);
  float posJugadorX, posJugadorY, alturaJugador;
  float anguloDeVista = 2*acos(0.0) / 3;
  float anguloJugador = 2*acos(0.0) / 3;
  int alturaParedProyectada = 0;
  int ladoMapa = LADO_CELDA * TAMANIO_FILA;

  Rayo rayo(anguloDeVista,LADO_CELDA,TAMANIO_FILA,LARGO_PROYECTOR);

  for (int i = TAMANIO_FILA/*esto hay que cambiarlo por ladoMapa*/; i > 0; i--){//como barremos antihorario, barremos de derecha a izquierda la pantalla
    float distancia = 0;
    if (rayo.verificarInterseccionHorizontal(mapa,distancia,anguloJugador)){
      alturaParedProyectada = (LADO_CELDA / distancia) * rayo.getDistanciaProyector();
      std::cout << "la altura es: " << alturaParedProyectada << "\n";
    }else if (rayo.verificarInterseccionVertical(mapa,distancia,anguloJugador)){
      alturaParedProyectada = (LADO_CELDA / distancia) * rayo.getDistanciaProyector();
      std::cout << "la altura es: " << alturaParedProyectada << "\n";

    }

  /*  if (distancia > 0){
      dibujarPared(alturaParedProyectada,i);
    }*/
    rayo.aumentarAnguloBarrido();
  }
  return 0;

}
