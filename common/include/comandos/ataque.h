#ifndef ATAQUE_H
#define ATAQUE_H
#define DANIO_MAX 10

#include "comandos/comando.h"
#include <iostream>

class Ataque : public Comando {
private:

public:
    /*
      * creara la clase ataque dejandola valida para uso
    */
    Ataque(int idJugador);
    /*
      * liberara la clase con sus recursos
    */
    ~Ataque();
    /*
      * serializara la clase y devolvera la inforamcion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializara la clase, la creara y la dejara en sus valores
      * correspondientes
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * ejecutara el comando y devolvera las correspondientes actualizaciones
    */  
    std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) override;
};

#endif
