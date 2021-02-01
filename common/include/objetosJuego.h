#ifndef _OBJETOS_JUEGO_H
#define _OBJETOS_JUEGO_H


enum class Type {
    empty = 0, door = 1, wall = 2, fakeDoor = 3, keyDoor = 4, comida = 5,
    kitsMedicos = 6, sangre = 7, balas = 8, lanzaCohetes = 9, ametralladora = 10,
    canionDeCadena = 11, llave = 12, tesoro = 13, cruz = 14, copa = 15, cofre = 16,
    corona = 17
};

enum class Accion {
    moverse = 0, rotarDerecha = 1, rotarIzquierda = 2, moverArriba = 3, moverAbajo = 4,
    rotar = 5, ataque = 6
};


#endif
