#ifndef _OBJETOS_JUEGO_H
#define _OBJETOS_JUEGO_H

#define TYPE_WALL_2 28
#define TYPE_WALL_3 29
#define TYPE_FAKE_DOOR 3
#define TYPE_WALL 2
#define TYPE_DOOR 1
#define TYPE_EMPTY 0
#define TYPE_KEY_DOOR 4
#define TYPE_FAKE_WALL 3

#include <vector>

class ObjetosJuego;

class Type {
public:
    Type(std::string name, int type) : name(name), type(type) {}

    std::string getName() { return this->name; }

    int getType() { return this->type; }

    ~Type() {}

private:

    std::string name;
    int type;

    friend class ObjetosJuego;

};

class ObjetosJuego {
public:
    static std::vector<Type> obtenerObjetos() {
        std::vector<Type> types;
        types.push_back(Type("empty", TYPE_EMPTY));
        types.push_back(Type("door", TYPE_DOOR));
        types.push_back(Type("wall", TYPE_WALL));
        types.push_back(Type("wall-2", TYPE_WALL_2));
        types.push_back(Type("wall-3", TYPE_WALL_3));
        types.push_back(Type("fakeDoor", TYPE_FAKE_DOOR));
        types.push_back(Type("keyDoor", 4));
        types.push_back(Type("comida", 5));
        types.push_back(Type("kitsMedicos", 6));
        types.push_back(Type("sangre", 7));
        types.push_back(Type("balas", 8));
        types.push_back(Type("lanzaCohetes", 9));
        types.push_back(Type("ametralladora", 10));
        types.push_back(Type("canionDeCadena", 11));
        types.push_back(Type("llave", 12));
        types.push_back(Type("tesoro", 13));
        types.push_back(Type("cruz", 14));
        types.push_back(Type("copa", 15));
        types.push_back(Type("cofre", 16));
        types.push_back(Type("corona", 17));
        types.push_back(Type("noItem", 18));
        types.push_back(Type("agua", 19));
        types.push_back(Type("mesa", 20));
        types.push_back(Type("lampara", 21));
        types.push_back(Type("muertoColgante", 22));
        types.push_back(Type("tanque", 23));
        types.push_back(Type("barril", 24));
        types.push_back(Type("planta", 24));
        types.push_back(Type("pistola", 25));
        types.push_back(Type("cuchillo", 27));
        return types;
    }

    static Type obtenerTipoPorId(int id) {
        for (Type t: obtenerObjetos()) {
            if (t.getType() == id)
                return t;
        }
        return Type("noItem", 18);
    }


    static Type obtenerTipoPorNombre(std::string nombre) {
        for (Type t: obtenerObjetos()) {
            if (t.getName() == nombre)
                return t;
        }
        return Type("noItem", 18);
    }

private:
    ObjetosJuego() {} //??
};

enum class Accion {
    moverse = 0, rotarDerecha = 1, rotarIzquierda = 2, moverArriba = 3, moverAbajo = 4,
    rotar = 5, ataque = 6, aperturaDePuerta = 7, crearPartida = 8, unirseAPartida = 9, cambioDeArma = 10
};


#endif
