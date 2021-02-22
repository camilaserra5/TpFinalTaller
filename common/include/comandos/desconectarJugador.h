#ifndef __DESCONECTAR_JUGADOR__
#define __DESCONECTAR_JUGADOR__

#include "comandos/comando.h"

class DesconectarJugador : public Comando {

public:
    /*
      * creara la clase desconcetar juagdor dejandola valida para uso
    */
    DesconectarJugador(int idJugador);
    /*
      * liberara la clase con sus recursos
    */
    ~DesconectarJugador();
    /*
      * ejecutara el comando y devolvera las actualizaciones correspondientes
    */
    std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) override;
    /*
      * serializar la clase devolviendo la informacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializara la clase, creandola y dejandola en sus valores
      * correspondientes
    */  
    void deserializar(std::vector<char> &serializado) override;

};


#endif
