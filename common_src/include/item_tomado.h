#ifndef MOVIMENTO_H
#define MOVIMIENTO_H
#include "comando.h"
#include "iserializable.h"

class ItemTomado: public Comando,public ISerializable{//en vez de heredar dde comando, deberia heredar de actualizacion creo
  private:
    int item = 1;
  public:
    ItemTomado() {}
    void serializar() override{}
    void deserializar() override{}
    void estrategia() override;
};

#endif
