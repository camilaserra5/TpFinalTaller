#ifndef POSICION_H
#define POSICION_H

#include "iserializable.h"

class Jugador;

class Posicion : public ISerializable {
public:
    /*
      * creara la clase posicion dejandola valida para uso
    */
    Posicion(int pixelesX, int pixelesY, float anguloDeVista);
    /*
      * liberara la clase
    */
    ~Posicion();
    /*
      * constrcutor por defautl
    */
    Posicion();
    /*
      * devuelve la distancia a la poscion que le llega
    */
    float distanciaA(Posicion &posicion);
    /*
      * devuelve true si interseca con mig angulo
    */
    bool intersectaConMiAngulo(Posicion &otroJugador);
    /*
      * actualiza la poscioon
    */
    void actualizar_posicion(int pixelesx, int pixelesy);
    /*
      * devuelve la poscion en x
    */
    int pixelesEnX();
    /*
      * devuelve la pocion en y
    */
    int pixelesEnY();
    /*
      * settea el angulo del juagdor
    */
    void setAngulo(float angulo);
    /*
      * devuelve el angulo de vida
    */
    float getAnguloDeVista() { return this->anguloDeVista; }
    /*
      * devuelve si esta cerca
    */
    bool estaCerca(int &posx, int &posy, float radio);
    /*
      * rita el angulo
    */
    void rotar(float anguloRotacion);
    /*
      * operador ==
    */
    bool operator==(Posicion &posicion);
    /*
      * serializa la clase y devuelve su infromacion
    */
    std::vector<char> serializar() override;
    /*
      * deserializa la clase cargandole sus valeres previos
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * verifica si la poscion dle otro juagdor pertenece a mi segmento
    */  
    bool verificarSiPerteneceAlSegmento(Posicion &otroJugador);

private:
    int pixelesX;
    int pixelesY;
    float anguloDeVista;
};

#endif
