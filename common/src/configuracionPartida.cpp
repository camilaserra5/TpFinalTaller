#include "../include/configuracionPartida.h"

void ConfiguracionPartida::setVRotacion(float vRotacion){
  this->vRotacion = vRotacion;
}
void ConfiguracionPartida::setVAvance(float vAvance){
  this->vAvance = vAvance;
}
void ConfiguracionPartida::setVidaMax(float vidaMax){
  this->vidaMax = vidaMax;
}
void ConfiguracionPartida::setBalasPorRafagaAmetralladora(int balasPorRafagaAmetralladora){
  this->balasPorRafagaAmetralladora = balasPorRafagaAmetralladora;
}
void ConfiguracionPartida::setBalasPorRafagaCanion(int balasPorRafagaCanion){
  this->balasPorRafagaCanion = balasPorRafagaCanion;
}
void ConfiguracionPartida::setMaxBalas(int maxBalas){
  this->maxBalas = maxBalas;
}
void ConfiguracionPartida::setCantidadBalasInicial(int cantidadBalasInicial){
  this->cantidadBalasInicial = cantidadBalasInicial;
}
void ConfiguracionPartida::setDistanciaMaxAcuchillable(float distanciaMaxAcuchillable){
  this->distanciaMaxAcuchillable = distanciaMaxAcuchillable;
}
void ConfiguracionPartida::setPuntos_cruz(float puntos_cruz){
  this->puntos_cruz = puntos_cruz;
}
void ConfiguracionPartida::setPunto_copa(float puntos_copa){
  this->puntos_copa = puntos_copa;
}
void ConfiguracionPartida::setPunto_cofre(float puntos_cofre){
  this->puntos_cofre = puntos_cofre;
}
void ConfiguracionPartida::setPuntos_corona(float puntos_corona){
  this->puntos_corona = puntos_corona;
}
void ConfiguracionPartida::setCantidadVidas(int cantidadVidas){
  this->cantidadVidas = cantidadVidas;
}
int ConfiguracionPartida::getBalasInicial(){
  return this->cantidadBalasInicial;
}
float ConfiguracionPartida::getVRotacion(){
  return this->vRotacion;
}
float ConfiguracionPartida::getVidaMax(){
  return this->vidaMax;
}
float ConfiguracionPartida::obtenerVAvance(){
  return this->vAvance;
}
