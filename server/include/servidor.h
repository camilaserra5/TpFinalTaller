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
    Servidor(Parser &parser, ConfiguracionPartida &config);

    void correr();

    void cerrar();

    ~Servidor();
};

#endif /*SERVIDOR_H*/
