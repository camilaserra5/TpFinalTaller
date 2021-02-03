#include "../include/logro.h"
#define PUNTOS_BALAS 5
#define PUNTOS_MATAR 10
bool Logro::operator>(Logro &logro) {
    bool mateMasEnemigos = (this->enemigosMatados > logro.enemigosMatados ? true : false);
    bool tengoMasPuntosPorTesoro = (this->puntosTotalesPorTesoros > logro.puntosTotalesPorTesoros ? true : false);
    bool dispareMasBalas = (this->balasDisparadas > logro.balasDisparadas ? true : false);
    return (mateMasEnemigos && tengoMasPuntosPorTesoro && dispareMasBalas);
}

bool Logro::operator==(Logro &logro) {
    bool mateMasEnemigos = (this->enemigosMatados == logro.enemigosMatados ? true : false);
    bool tengoMasPuntosPorTesoro = (this->puntosTotalesPorTesoros == logro.puntosTotalesPorTesoros ? true : false);
    bool dispareMasBalas = (this->balasDisparadas == logro.balasDisparadas ? true : false);
    return (mateMasEnemigos && tengoMasPuntosPorTesoro && dispareMasBalas);
}

void Logro::aniadirBalasDisparadas(int cantidadDeBalas) {
    this->balasDisparadas += cantidadDeBalas;
}

void Logro::aniadirPuntosPorTesoro(int puntos) {
    this->puntosTotalesPorTesoros += puntos;
} //cada tesoro sabe cuantos puntos

void Logro::aniadirEnemigosMatados(int cantidadDeEnemigos) {
    this->enemigosMatados += cantidadDeEnemigos;
}
int Logro::obtenerPuntosTotales(){
    return (this->puntosTotalesPorTesoros + this->enemigosMatados*PUNTOS_MATAR +
            this->balasDisparadas*PUNTOS_BALAS);
}
