#ifndef POSICION_H
#define POSICION_H

class Jugador;
class Posicion{
  public:
    Posicion(int metrosX,int metrosY,float anguloDeVista):
    metrosX(metrosX),
    metrosY(metrosY),
    anguloDeVista(anguloDeVista){
      //calculo de la posicion dentro de la matriz
    }
    ~Posicion(){}
    int distanciaA(Posicion &posicion){ return -1;}
    int intersectaConMiAngulo(Posicion &otroJugador){ return -1;}
  private:
    int metrosX;
    int metrosY;
    int posicionMapaX;
    int posicionMapaY;
    float anguloDeVista;
};

#endif
