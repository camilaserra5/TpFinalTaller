#include "../include/contenedorDeElementos.h"
#include <iostream>

std::vector<char> ContenedorDeElementos::serializar(){
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(elementos.size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    for (auto &elemento : elementos) {
        std::vector<char> itemSerializado = ((Item *) elemento)->serializar();
        aux = numberToCharArray(itemSerializado.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        informacion.insert(informacion.end(), itemSerializado.begin(),
                            itemSerializado.end());
    }
    return informacion;
}

void ContenedorDeElementos::deserializar(std::vector<char> &serializado){
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int elementosSize = charArrayToNumber(sub);
    idx += 4;
    for (int i = 0; i < elementosSize; i++) {
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        idx += 4;
        std::vector<char> itemSerializado(serializado.begin() + idx,
                            serializado.begin() + idx + charArrayToNumber(sub));
        idx += charArrayToNumber(sub);
        Item *item;
        item->deserializar(itemSerializado);
        this->elementos.push_back(item);
    }
}

std::vector<Item *>& ContenedorDeElementos::obtenerItems() {
    return this->elementos;
}


Puerta& ContenedorDeElementos::puertaMasCercana(Posicion& posicionJugador,
                                                double& distancia){
  int cantPuertas = this->puertas.size();
  int posPuertaMasCercana = 0;
  distancia = this->puertas[0].distanciaA(posicionJugador);
    for (int i = 1; i < cantPuertas; i++){
      double distanciaParcial = this->puertas[i].distanciaA(posicionJugador);
      if (distanciaParcial < distancia){
          distancia = distanciaParcial;
          posPuertaMasCercana = i;
      }
    }
    return this->puertas[posPuertaMasCercana];
}

void ContenedorDeElementos::agregarElemento(Item *item) {
    this->elementos.push_back(item);
}

void ContenedorDeElementos::sacarElementoDePosicion(Posicion &posicion) {
    std::vector<Item *> elementosFiltrados;
    for (int i = 0; i < this->elementos.size(); i++) {
        if (this->elementos[i]->obtenerPosicion() == posicion) {
            delete this->elementos[i];
        } else {
            elementosFiltrados.push_back(this->elementos[i]);
        }
    }
    this->elementos.swap(elementosFiltrados);
}

ContenedorDeElementos::ContenedorDeElementos() :
        elementos() {}

ContenedorDeElementos::~ContenedorDeElementos() {}

Item *ContenedorDeElementos::buscarElemento(int &posx, int &posy) {
    for (int i = 0; i < this->elementos.size(); i++) {
        if (this->elementos[i]->estaCerca(posx, posy)) {
            return this->elementos[i];
        }
    }
    return nullptr;
}

bool ContenedorDeElementos::hayPuertas(){
  return (this->puertas.size() > 0);
}
