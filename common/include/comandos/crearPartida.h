#ifndef CREAR_PARTIDA_H
#define CREAR_PARTIDA_H

#include "comando.h"

class CrearPartida : public Comando {

private:
    int cantidadJugadores;
    std::string nombrePartida;
    std::string rutaYaml;
    std::string nombreCliente;
    int screenWidth;

public:
    /*
      * creara la clase crear partida dejandola valida para uso
    */
    CrearPartida(int idJugador, int cantidadJugadores,
                 std::string nombrePartida, std::string rutaYaml,
                 std::string nombreCliente, int screenWidth);
    /*
      * liberara la clase con sus recursos
    */
    ~CrearPartida();
    /*
      * constrcutor poe default
    */
    CrearPartida();
    /*
      * serializara la clase, devolviendo la informacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializara la clase, creandola y dejandola en sus valores
      * correspondiente
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * ejecutara el comando y devolvera la actualizacion correspondiente
    */
    std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) override {
        std::vector<Actualizacion *> a;
        return a;
    }
    /*
      * devuelve el nombre dle juagdor
    */
    std::string &getNombreJugador();
    /*
      * devuelve el nombre de la partida
    */
    std::string &getNombrePartida();
    /*
      * devuelve la cnatidad de jugadores que se quiere en la partida
    */
    int &getCantJugadores();
    /*
      * devuelve la ruta del archivo
    */
    std::string &getRutaArchivo();
    /*
      * devuelve en ancho de la pantalla
    */  
    int &getScreenWidth();


};

#endif
