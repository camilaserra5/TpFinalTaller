#ifndef WOLFSTEIN_JUGADORLUA_H
#define WOLFSTEIN_JUGADORLUA_H

#include "thread.h"
#include "modelo.h"
#include "../src/LUA/manejadorlua.h"
#include <string>

class JugadorLua : public Thread{
private:
    Modelo & modelo;
    ManejadorLua lua;
    bool esta_vivo;

public:
    JugadorLua(Modelo& modelo/*, std::string IDJugador*/);
    void run() override;
    void stop();
    ~JugadorLua() {}
};


#endif //WOLFSTEIN_JUGADORLUA_H
