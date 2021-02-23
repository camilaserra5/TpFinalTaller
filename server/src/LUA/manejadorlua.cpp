#include "manejadorlua.h"
#include <iostream>

#define MAPA "mapa"


ManejadorLua::ManejadorLua(std::string &archivo) {
    std::cerr << "=== INSTANCIANDO UN MANEJADOR LUA==== " << std::endl;
    interprete = luaL_newstate();
    luaL_openlibs(interprete);
    luaL_dofile(interprete, archivo.c_str());
}

void ManejadorLua::vaciarStack() {
    int stackSize = lua_gettop(interprete);
    while (stackSize != 0) {
        lua_pop(interprete, 1);
        stackSize = lua_gettop(interprete);
    }
}

ManejadorLua::~ManejadorLua() {
    vaciarStack();
    lua_close(interprete);
}

/* Crea una tabla en lua que es guardada en el stack
 * para ser usada por el script
 */
void ManejadorLua::crearTabla(std::vector<std::vector<int>> &mapa, std::string nombremapa) {
    std::cerr << "=== CREANDO TABLA LUA==== " << std::endl;
    lua_newtable(interprete);
    int tamanioMapa = mapa.size();
    for (int i = 0; i < tamanioMapa; i++) {
        lua_pushnumber(interprete, i + 1);    // indice de la tabla
        lua_newtable(interprete);                    // tabla
        int size = mapa[i].size();
        for (int j = 0; j < size; j++) {
            lua_pushnumber(interprete, j + 1);       // indice del valor
            lua_pushnumber(interprete, mapa[i][j]);     // valor
            lua_settable(interprete, -3);
        }
        lua_settable(interprete, -3);
    }
    lua_setglobal(interprete, nombremapa.c_str());
}

void ManejadorLua::crearMapa(std::vector<std::vector<int>> mapa) {
    std::cerr << "=== CREANDO MAPA LUA==== " << std::endl;
    this->mapaLargo = mapa.size();
    this->mapaAncho = mapa[0].size();
    crearTabla(mapa, MAPA);
}

const char *ManejadorLua::generarEvento(int &posx, int &posy,
                    std::vector<int>& posiciones_jugadores, int cantJugadores,
                    int &posPixelX, int &posPixelY) {
    std::cerr << "=== MANEJADOR LUA GENERAR EVENTO==== " << std::endl;
    lua_getglobal(interprete, "crear_accion");

    lua_pushnumber(interprete, posx);
    lua_pushnumber(interprete, posy);
    lua_pushnumber(interprete, cantJugadores);
    lua_pushnumber(interprete, posPixelX);
    lua_pushnumber(interprete, posPixelY);
    lua_newtable(interprete);//tabla esta en el top del stack
    for (int i = 0; i < cantJugadores*2; i++) {
        lua_pushnumber(interprete, posiciones_jugadores.at(i));//ahora hay un numero arriba de todo
        lua_rawseti(interprete,-2,i+1); //inserta el numero en la tabla y la tabla vuelve a estar en el top
    }
    lua_pcall(interprete, 6, 1, 0);
    const char *tecla = lua_tostring(interprete, 1);
    lua_pop(interprete, 1); // elimina
    //std::cerr << "=== LUA ME DEVOLVIO: " << tecla << " ==== " << std::endl;
    return tecla;
}
