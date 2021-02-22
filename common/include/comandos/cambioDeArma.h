#ifndef CAMBIO_DE_ARMA
#define CAMBIO_DE_ARMA

#include "comandos/comando.h"

class CambioDeArma : public Comando {

public:
    /*
      * creara la clase cambio de arma dejandola valida para uso
    */
    CambioDeArma(int idJugador) : Comando(idJugador) {}
    /*
      * liberara la clase con sus recursos
    */
    ~CambioDeArma() {}
    /*
      * ejecutara el comando y devolvera lasactualizaciones correspondientes
    */
    std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) override;
    /*
      * serializara la clase y devolvera la informacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializara la clase, creandola y dejandola en sus valores correspondientes
    */  
    void deserializar(std::vector<char> &serializado) override;

};

#endif
