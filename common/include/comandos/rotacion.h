#ifndef ROTACION_H
#define ROTACION_H

#include "comando.h"
#include "iserializable.h"

class Rotacion : public Comando, public ISerializable {

private:
  //Accion sentidoDeRotacion;
public:

  Rotacion(Accion sentidoDeRotacion): sentidoDeRotacion(sentidoDeRotacion){}

  std::stringstreamvoid serializar() override{}

  void deserializar(/*std::stringstream secuencia*/)override{}

  void ejecutar(EstadoJuego &EstadoJuego) override{}

  ~Rotacion();
};

#endif
