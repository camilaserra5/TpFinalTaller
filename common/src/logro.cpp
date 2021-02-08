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

int Logro::obtenerPuntosTotales() {
    return (this->puntosTotalesPorTesoros + this->enemigosMatados * PUNTOS_MATAR +
            this->balasDisparadas * PUNTOS_BALAS);
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
//    std::cerr << " logro deserializar emp "  << std::endl;
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->enemigosMatados = charArrayToNumber(sub);
  //  std::cerr << " logro deserializar enemigosMatados " << enemigosMatados << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->puntosTotalesPorTesoros = charArrayToNumber(sub);
//    std::cerr << " logro deserializar puntosTotalesPorTesoros " << puntosTotalesPorTesoros << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->balasDisparadas = charArrayToNumber(sub);
  //  std::cerr << " logro deserializar balasDisparadas " << balasDisparadas << std::endl;
  //  std::cerr << " logro deserializar fin "  << std::endl;
}
