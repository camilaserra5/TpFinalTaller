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
    int distanciaA(Posicion &posicion);
    bool intersectaConMiAngulo(Posicion &otroJugador);
  private:
    int pixelesX;
    int pixelesY;
    int posicionMapaX;
    int posicionMapaY;
    float anguloDeVista;
};

#endif
