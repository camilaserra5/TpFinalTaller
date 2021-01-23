#ifndef _OBJETOS_JUEGO_H
#define _OBJETOS_JUEGO_H



enum class Type {
    empty = 0, door = 1, wall = 2, fakeDoor = 3, keyDoor = 4, comida = 5,
    kitsMedicos = 6, sangre = 7, balas = 8, lanzaCohetes = 9, ametralladora = 10,
    canionDeCadena = 11, llave = 12, tesoro = 13
};

enum class Accion{
    moverDerecha = 1, moverIzquierda = 2, moverArriba = 3, moverAbajo = 4,
    rotar = 5, atacar = 6
};
