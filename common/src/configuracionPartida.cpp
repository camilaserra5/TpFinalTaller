#include <iostream>
#include "../include/configuracionPartida.h"

void ConfiguracionPartida::setVRotacion(float vRotacion) {
    this->vRotacion = vRotacion;
}

void ConfiguracionPartida::setVAvance(float vAvance) {
    this->vAvance = vAvance;
}

void ConfiguracionPartida::setVidaMax(float vidaMax) {
    this->vidaMax = vidaMax;
}

void ConfiguracionPartida::setBalasPorRafagaAmetralladora(int balasPorRafagaAmetralladora) {
    this->balasPorRafagaAmetralladora = balasPorRafagaAmetralladora;
}

void ConfiguracionPartida::setBalasPorRafagaCanion(int balasPorRafagaCanion) {
    this->balasPorRafagaCanion = balasPorRafagaCanion;
}

void ConfiguracionPartida::setBalasPorRafagaPistola(int balasPorRafagaPistola){
  this->balasPorRafagaPistola = balasPorRafagaPistola;
}

void ConfiguracionPartida::setMaxBalas(int maxBalas) {
    this->maxBalas = maxBalas;
}

void ConfiguracionPartida::setCantidadBalasInicial(int cantidadBalasInicial) {
    this->cantidadBalasInicial = cantidadBalasInicial;
}

void ConfiguracionPartida::setDistanciaMaxAcuchillable(float distanciaMaxAcuchillable) {
    this->distanciaMaxAcuchillable = distanciaMaxAcuchillable;
}

void ConfiguracionPartida::setPuntos_cruz(float puntos_cruz) {
    this->puntosCruz = puntos_cruz;
}

void ConfiguracionPartida::setPunto_copa(float puntos_copa) {
    this->puntosCopa = puntos_copa;
}

void ConfiguracionPartida::setPunto_cofre(float puntos_cofre) {
    this->puntosCofre = puntos_cofre;
}

void ConfiguracionPartida::setPuntos_corona(float puntos_corona) {
    this->puntosCorona = puntos_corona;
}

void ConfiguracionPartida::setCantidadVidas(int cantidadVidas) {
    this->cantidadVidas = cantidadVidas;
}

void ConfiguracionPartida::setPuntosBalas(int puntosBalas){
  this->puntosBalas = puntosBalas;
}

void ConfiguracionPartida::setPuntosMatar(int puntosMatar){
  this->puntosMatar = puntosMatar;
}

void ConfiguracionPartida::setDanioMaximoArma(int danio_maximo_arma){
  this->danio_maximo_arma = danio_maximo_arma;
}

int ConfiguracionPartida::getBalasInicial() {
    return this->cantidadBalasInicial;
}

float ConfiguracionPartida::getVRotacion() {
    return this->vRotacion;
}

int ConfiguracionPartida::getVidaMax() {
    return this->vidaMax;
}

float ConfiguracionPartida::obtenerVAvance() {
    return this->vAvance;
}

int ConfiguracionPartida::getCantidadDeVidas(){
  return this->cantidadVidas;
}

int ConfiguracionPartida::getPuntosCruz(){
  return this->puntosCruz;
}

int ConfiguracionPartida::getPuntosCopa(){
  return this->puntosCopa;
}

int ConfiguracionPartida::getPuntosCofre(){
  return this->puntosCofre;
}

int ConfiguracionPartida::getPuntosCorona(){
  return this->puntosCorona;
}

int ConfiguracionPartida::getPuntosBalas(){
  return this->puntosBalas;
}

int ConfiguracionPartida::getPuntosMatar(){
  return this->puntosMatar;
}

int ConfiguracionPartida::getDanioMaximoArma(){
  return this->danio_maximo_arma;
}

int ConfiguracionPartida::getBalasPorRafagaAmetralladora(){
  return this->balasPorRafagaAmetralladora;
}

int ConfiguracionPartida::getBalasPorRafagaCanion(){
  return this->balasPorRafagaCanion;
}

int ConfiguracionPartida::getBalasPorRafagaPistola(){
  return this->balasPorRafagaPistola;
}
