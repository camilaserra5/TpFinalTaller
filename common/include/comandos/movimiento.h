#ifndef MOVIMENTO_H
#define MOVIMIENTO_H

#include "comando.h"
#include "estadoJuego.h"
#include <iostream>

class Movimiento : public Comando {
private:
    Accion tipo_de_movimiento;
public:
    /*
      * creara la clase movimiento dejandola valida para uso
    */
    Movimiento(int &idJugador, Accion tipo_de_movimiento);
    /*
      * ejecutara el comando y devolvera las actualizaciones correspondientes
    */
    std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) override;
    /*
      * liberara la clase con sus recursos
    */
    ~Movimiento();
    /*
      * constructor por defautl
    */
    Movimiento();
    /*
      * serializara la clase y devolvera la informacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserilizara la clase, creandola y dejandola en sus valores
      * correspindientes
    */  
    void deserializar(std::vector<char> &serializado) override;
};

#endif
