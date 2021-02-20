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

class Servidor {
private:
    Socket socket;
    Parser &parser;
public:
    Servidor(Parser &parser);

    void correr();

    ~Servidor();
};

#endif /*SERVIDOR_H*/
