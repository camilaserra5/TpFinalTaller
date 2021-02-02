/*
#include "manejadorlua.h"

ManejadorLua::ManejadorLua(){
    interprete = luaL_newstate();
}

void ManejadorLua::vaciarStack() {
    int stackSize = lua_gettop(interprete);
    while(stackSize != 0) {
        lua_pop(interprete, 1);
        stackSize = lua_gettop(interprete);
    }
}

ManejadorLua::~ManejadorLua() {
    vaciarStack();
    lua_close(interprete);
}*/
