#include "map.h"
#include <math.h>

void dibujarPared(int alturaParedProyectada,int stripe){

}

//falta plantear cuando hay que restar 64 a ya y xa
bool verificarParedHorizontal(Map& mapa,int ladoCelda,int anguloPorStripe, int& distancia){
  bool encontrePared = false;
  int xa = ladoCelda / tan(anguloPorStripe);
  int posX = 10, posY = 10;
  int posXPared = posX, posYPared = posY;
  int largoFila = mapa.getRowSize();
  int largoColumna = mapa.getColSize();
  while (!encontrePared && posX < largoFila && posY < largoColumna){
    if (mapa(posX,posY) == 2){
      encontrePared = true;
      posX -= posXPared;
      posY -= posYPared;
      distancia = sqrt((posX * posX) + (posY * posY));
    }
    posX += xa;
    posY += ladoCelda;
  }
  return encontrePared;
}

bool verificarParedVertical(Map& mapa,int ladoCelda,int anguloPorStripe, int& distancia){
  bool encontrePared = false;
  int ya = ladoCelda / tan(anguloPorStripe);
  int posX = 10, posY = 10;
  int posXPared = posX, posYPared = posY;
  int largoFila = mapa.getRowSize();
  int largoColumna = mapa.getColSize();
  while (!encontrePared && posX < largoFila && posY < largoColumna){
    if (mapa(posX,posY) == 2){
      encontrePared = true;
      posX -= posXPared;
      posY -= posYPared;
      distancia = sqrt((posX * posX) + (posY * posY));
    }
    posY += ya;
    posX += ladoCelda;
  }
  return encontrePared;
}

int main (){
  Map mapa;
  int posJugadorX, posJugadorY, alturaJugador;
  int anguloDeVista = 60, ladoCelda, largoProyector, anchoProyector;
  int distanciaProyector = (largoProyector / 2) / tan(anguloDeVista / 2);
  int ladoMapa = 320;
  int anguloPorStripe = ladoMapa / anguloDeVista;
  for (int i = 0; i < ladoMapa; i++){
    int distancia = 0;
    if (verificarParedHorizontal(mapa,ladoCelda,anguloPorStripe,distancia)){
      int alturaParedProyectada = (ladoCelda / distancia) * distanciaProyector;
    }else if (verificarParedVertical(mapa,ladoCelda,anguloPorStripe,distancia)){
      int alturaParedProyectada = (ladoCelda / distancia) * distanciaProyector;
    }
    if (distancia > 0){
      dibujarPared(alturaParedProyectada,i);
    }
    anguloPorStripe += anguloPorStripe;
  }


}
