#ifndef MOVIMENTO_H
#define MOVIMIENTO_H
#include "comando.h"
#include "iserializable.h"

class Movimiento: public Comando, public ISerializable{
  private:
    int tecla_asociada = 1;
  public:
    Movimiento() {}
    void estrategia() override;
    void serializar() override{}
    void deserializar() override{}
};
#endif
