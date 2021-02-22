#ifndef UNIRSE_A_PARTIDA
#define UNIRSE_A_PARTIDA

#include "comando.h"

class UnirseAPartida : public Comando {

private:
    std::string nombrePartida;
    std::string nombreCliente;

public:
    /*
      * creara la clase uniser a partida dejandola valida para uso
    */
    UnirseAPartida(int idJugador, std::string nombrePartida,
                   std::string nombreCliente);
    /*
      * liberara la clase con sus recursos
    */
    ~UnirseAPartida();
    /*
      * constructor por default
    */
    UnirseAPartida();
    /*
      *serializara la clase y devolvera la informacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializara la clase crandola y dejandola en sus valores
      * corrspondientes
    */  
    void deserializar(std::vector<char> &serializado) override;

    std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) override {
        std::vector<Actualizacion *> a;
        return a;
    }

    std::string &getNombreJugador();

    std::string &getNombrePartida();
};

#endif
