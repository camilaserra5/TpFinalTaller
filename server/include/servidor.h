#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include <map>
#include "thread.h"
#include "protected_queue.h"
#include "actualizaciones/actualizacion.h"
#include "comandos/comando.h"
#include "map.h"
#include "estadoJuego.h"
#include "jugador.h"
#include "iserializable.h"
#include <atomic>
#include "jugadorLua.h"
#include "parser.h"
#include <string>
#include "socket.h"
#include "aceptador.h"
#include "configuracionPartida.h"

class Servidor {
private:
    Socket socket;
    Parser &parser;
    Aceptador aceptador;
public:
    /*
      * creara la clase server djenadola valida para uso
      * sus parametros deben estar inicalizados
    */
    Servidor(Parser &parser, ConfiguracionPartida &config);
    /*
      * levanta al servidor
    */
    void correr();
    /*
      * cierra el socket y hace join del aceptador
    */
    void cerrar();
    /*
      * liberara la clase servidor 
    */
    ~Servidor();
};

#endif /*SERVIDOR_H*/
