#ifndef POSICION_H
#define POSICION_H

class Jugador;
class Posicion{
  public:
    Posicion(int posicionX,int posicionY,float anguloDeVista):
    metrosX(posicionX),
    metrosY(posicionY),
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
