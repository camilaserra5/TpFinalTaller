#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <string>
#include <vector>
#include "thread.h"
#include "socket.h"
#include "../include/thclient.h"
#include "configuracionPartida.h"

class Aceptador : public Thread {
private:
    Socket &socket_listener;
    std::vector<ThClient *> clientes;
    std::string rutaMapas;
    std::map<std::string, std::string> mapas;
    ProtectedQueue<Comando *> cola_comandos;
    int generadorDeId = 100;
    ConfiguracionPartida configuracionPartida;

    int obtenerIdParaJugador();

public:
    /*
      * creara la clase acpetador dejandola valida para uso
      * suspametros deben estar inicializados
    */
    Aceptador(Socket &un_socket, std::string rutaMapas,
              std::map<std::string, std::string> mapas,
              ConfiguracionPartida configuracion);
    /*
      * ejecuta el loop de ir aceptando clientes e ir limpiandolos cuando
      * terminan . Tambien liberara las partidas terminadas.
    */
    void run() override;
    /*
      * cerrara el socket listener
    */
    void cerrar();
    /*
      * liberara a la clase
    */
    ~Aceptador(){}
};

#endif /*ACEPTADOR_H*/
