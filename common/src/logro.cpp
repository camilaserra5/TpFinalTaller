#include "../include/logro.h"

bool operator>(Logro& logro){
  bool mateMasEnemigos = (this->enemigosMatados > logro.enemigosMatados? true:false);
  bool tengoMasPuntosPorTesoro = (this->puntosTotalesPorTesoros > logro.puntosTotalesPorTesoros? true:false);
  bool dispareMasBalas = (this->balasDisparadas > logro.balasDisparadas? true:false);
  return (mateMasEnemigos && tengoMasPuntosPorTesoro && dispareMasBalas);
}

bool operator==(Logro &logro){
  bool mateMasEnemigos = (this->enemigosMatados == logro.enemigosMatados? true:false);
  bool tengoMasPuntosPorTesoro = (this->puntosTotalesPorTesoros == logro.puntosTotalesPorTesoros? true:false);
  bool dispareMasBalas = (this->balasDisparadas == logro.balasDisparadas? true:false);
  return (mateMasEnemigos && tengoMasPuntosPorTesoro && dispareMasBalas);
}
void aniadirBalasDisparadas(int cantidadDeBalas);
void aniadirPuntosPorTesoro(int puntos); //cada tesoro sabe cuantos puntos
void aniadirEnemigosMatados(int cantidadDeEnemigos);
