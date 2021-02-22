#ifndef __APERTURA_DE_PUERTA__
#define __APERTURA_DE_PUERTA__

#include "comandos/comando.h"

class AperturaDePuerta : public Comando {

public:
    /*
      * creara el comando apertura de puerta dejandolo valido para uso
    */
    AperturaDePuerta(int idJugador);
    /*
      * liberara la clase con sus recursos
    */
    ~AperturaDePuerta();
    /*
      * ejecutara el comando y devolvera las corresponidnetes actualizaciones
    */
    std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) override;
    /*
      * serializara la clase y devolvera la inforacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializara la clase creandola y dejandola en sus valores correspondientes
    */  
    void deserializar(std::vector<char> &serializado) override;

};


#endif
