#include <iostream>
#include <math.h>

int verificarCuadranteY(float anguloPorStripe,float anguloJugador,int ladoCelda){
    float anguloBarrido = anguloJugador;
    if (anguloPorStripe < 2*acos(0.0) / 6){
      anguloBarrido = anguloJugador - anguloPorStripe;
    }else{
       anguloBarrido = anguloJugador + anguloPorStripe;
    }
  if (0 <= anguloBarrido && anguloBarrido <= 2*acos(0.0)){
    return ladoCelda;
  }else{
    return -ladoCelda;
  }
}
int verificarCuadranteX(float anguloPorStripe,float anguloJugador,int ladoCelda){
    float anguloBarrido = anguloJugador;
    if (anguloPorStripe < 2*acos(0.0) / 6){
      anguloBarrido = anguloJugador - anguloPorStripe;
    }else{
       anguloBarrido = anguloJugador + anguloPorStripe;
    }
  if (acos(0.0) <= anguloBarrido && anguloBarrido <= 3*acos(0.0)){
    return -ladoCelda;
  }else{
    return ladoCelda;
  }
}

void dibujarPared(int alturaParedProyectada,int stripe){

}

//falta plantear cuando hay que restar 64 a ya y xa
bool verificarParedHorizontal(int mapa[][20],float ladoCelda,float anguloPorStripe, float& distancia){
  bool encontrePared = false;
  float xa = ladoCelda / tan(anguloPorStripe);
  int posX = 4, posY = 2;
  float anguloJugador = 2*acos(0.0) / 3;//pi / 3

  int posXPared = posX, posYPared = posY;
  int largoFila = 20;
  int largoColumna = 20;
  while (!encontrePared && 0 < posX && posX < largoFila &&  0 < posY && posY < largoColumna){
    if (mapa[posX][posY] == 2/*Type::wall*/){
      encontrePared = true;
      posX -= posXPared;
      posY -= posYPared;
      distancia = sqrt((posX * posX) + (posY * posY));
    }
    posX += xa;
    posY += verificarCuadranteY(anguloPorStripe,anguloJugador,ladoCelda);
  }
  return encontrePared;
}

bool verificarParedVertical(int mapa[][20],float ladoCelda,float anguloPorStripe, float& distancia){
  bool encontrePared = false;
  float ya = ladoCelda / tan(anguloPorStripe);
  int posX = 4, posY = 2;
  int posXPared = posX, posYPared = posY;
  int largoFila = 20;
  int largoColumna = 20;
  float anguloJugador = 2*acos(0.0) / 3;//pi / 3
  while (!encontrePared && 0 < posX && posX < largoFila &&  0 < posY && posY < largoColumna){
    if (mapa[posX][posY] == 2/*Type::wall*/){
      encontrePared = true;
      posX -= posXPared;
      posY -= posYPared;
      distancia = sqrt((posX * posX) + (posY * posY));
    }
    posY += ya;
    posX += verificarCuadranteX(anguloPorStripe,anguloJugador,ladoCelda);
  }
  return encontrePared;
}

int main (){
//  Juego juego;
//  juego.inicializar("Wolfstein", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
  //Map mapa = MapTranslator::yamlToMap(YAML::LoadFile("../editor/src/config.yaml"));
  int mapa[20][20] = {{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                      {2,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2},
                      {2,2,0,0,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2},
                      {2,2,0,0,2,2,0,2,2,2,2,0,0,0,0,2,2,2,2,2},
                      {2,2,0,0,0,2,0,2,2,2,2,0,2,2,0,2,2,2,2,2},
                      {2,2,0,0,2,2,0,0,0,0,0,0,2,2,0,2,2,2,2,2},
                      {2,2,0,2,2,2,0,2,2,2,2,0,2,2,2,2,2,2,2,2},
                      {2,2,0,2,2,2,0,2,2,2,2,0,2,2,2,2,2,2,2,2},
                      {2,2,0,2,2,2,0,2,2,2,2,0,2,2,2,2,2,2,2,2},
                      {2,2,0,2,2,2,0,2,2,2,2,0,2,2,2,2,2,2,2,2}};

  float posJugadorX, posJugadorY, alturaJugador;
  float anguloDeVista = 2*acos(0.0) / 3, ladoCelda = 2, largoProyector = 20, anchoProyector = 20;
  float distanciaProyector = (largoProyector / 2) / tan(anguloDeVista / 2);
  float ladoMapa = 20; // lado celda * tamnaio de cada fila
  float anguloPorStripe = ladoMapa / anguloDeVista;
  int alturaParedProyectada = 0;
  for (int i = 0; i < ladoMapa; i++){
    float distancia = 0;
    if (verificarParedHorizontal(mapa,ladoCelda,anguloPorStripe,distancia)){
      alturaParedProyectada = (ladoCelda / distancia) * distanciaProyector;
      std::cout << "la altura es: " << alturaParedProyectada << "\n";
    }else if (verificarParedVertical(mapa,ladoCelda,anguloPorStripe,distancia)){
      alturaParedProyectada = (ladoCelda / distancia) * distanciaProyector;
      std::cout << "la altura es: " << alturaParedProyectada << "\n";
    }
    std::cout << "la altura es: " << alturaParedProyectada << "\n";

    if (distancia > 0){
      dibujarPared(alturaParedProyectada,i);
    }
    anguloPorStripe += anguloPorStripe;
  }


}
