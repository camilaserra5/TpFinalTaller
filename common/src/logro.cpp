#include "../include/logro.h"

bool Logro::operator>(Logro &logro) {
    bool mateMasEnemigos = this->enemigosMatados > logro.enemigosMatados;
    bool tengoMasPuntosPorTesoro = this->puntosTotalesPorTesoros > logro.puntosTotalesPorTesoros;
    bool dispareMasBalas = this->balasDisparadas > logro.balasDisparadas;
    return (mateMasEnemigos && tengoMasPuntosPorTesoro && dispareMasBalas);
}

Logro::Logro(){}

bool Logro::operator==(Logro &logro) {
    bool mateMasEnemigos = this->enemigosMatados == logro.enemigosMatados;
    bool tengoMasPuntosPorTesoro = this->puntosTotalesPorTesoros == logro.puntosTotalesPorTesoros;
    bool dispareMasBalas = this->balasDisparadas == logro.balasDisparadas;
    return (mateMasEnemigos && tengoMasPuntosPorTesoro && dispareMasBalas);
}

void Logro::aniadirBalasDisparadas(int cantidadDeBalas) {
    this->balasDisparadas += cantidadDeBalas;
}

void Logro::aniadirPuntosPorTesoro(int puntos) {
    this->puntosTotalesPorTesoros += puntos;
}

void Logro::aniadirEnemigosMatados(int cantidadDeEnemigos) {
    this->enemigosMatados += cantidadDeEnemigos;
}

int Logro::obtenerPuntosTotales() {
    return (this->puntosTotalesPorTesoros + this->enemigosMatados * this->puntosMatar +
            this->balasDisparadas * this->puntosBalas);
}

std::vector<char> Logro::serializar() {
    std::vector<char> info;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->enemigosMatados);

    info.insert(info.end(), aux.begin(), aux.end());

    aux = numberToCharArray(this->puntosTotalesPorTesoros);
    info.insert(info.end(), aux.begin(), aux.end());

    aux = numberToCharArray(this->balasDisparadas);
    info.insert(info.end(), aux.begin(), aux.end());
    return info;
}

void Logro::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->enemigosMatados = charArrayToNumber(sub);
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->balasDisparadas = charArrayToNumber(sub);
}
