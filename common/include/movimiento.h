#ifndef MOVIMENTO_H
#define MOVIMIENTO_H
#include "comando.h"
#include "iserializable.h"
#include "estadoJuego.h"

class Movimiento: public Comando, public ISerializable{
  private:
    int tipo_de_movimiento;
    int idJugador;
  public:
    Movimiento(int& idJugador, int& tipo_de_movimiento);
    void estrategia(EstadoJuego& EstadoJuego) override;
    ~Movimiento();
    void serializar() override{}
    void deserializar() override{}
};
#endif
