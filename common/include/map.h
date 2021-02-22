#ifndef MAP_H
#define MAP_H

#include <vector>
#include "contenedorDeElementos.h"
#include "items/item.h"
#include "objetosJuego.h"
#include "iserializable.h"
#include <iostream>
#include "puerta.h"
// faltaria agregar una posicion para los jugadores
// tambien el tema de los itemas(comida, sangre, todas las armas);

class Map : public ISerializable {
public:
//largo preconcatenado
    Map(unsigned rowSize, unsigned colSize, int anchoPantalla);

    unsigned getRowSize() const;

    unsigned getColSize() const;

    void setValue(const unsigned rowNumber, const unsigned colNumber, Type value);

    Type &operator()(const unsigned rowNumber, const unsigned colNumber);

    void crearElementoPosicionable(const unsigned rowNumber, const unsigned colSize, Type value);

    Item *buscarElemento(int &posx, int &posy);

    ContenedorDeElementos &obtenerContenedor();

    void sacarDelMapa(Posicion &posicion);

    ~Map();

    void agregarElemento(Item *item);

    void aniadirPuerta(const unsigned rowNumber, const unsigned colNumber, int tipoPuerta);

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    std::vector<Item *> &obtenerItems();

    Puerta &puertaMasCercana(Posicion &posicionJugador, double &distancia);

    bool hayPuertas();

    void agregarArma(Posicion &posicion, Arma *arma);

    int crearIdValido();

    bool hayColision(int fila, int columna);

    Posicion obtenerPosicionInicialValida();

    Map() {}//capaz poner privado

    void setLadoCelda(int anchoPantalla);

    int getLadoCelda();

    std::vector<std::vector<int>> getMapanumerico();

    Map(Map&& mapa);
    Map& operator=(Map&& mapa){
      if (this == &mapa) {
          return *this;
      }
      this->rowSize = mapa.rowSize;
      this->colSize = mapa.colSize;
      this->contenedorDeElementos = std::move(mapa.contenedorDeElementos);
      this->map = mapa.map;
      this->ladoCelda= mapa.ladoCelda;
      this->generadorDeId = mapa.generadorDeId;
      return *this;
    }
private:
    unsigned rowSize;
    unsigned colSize;
    ContenedorDeElementos *contenedorDeElementos;
    std::vector<std::vector<Type>> map;
    std::vector<int> idCargados;
    int ladoCelda;
    int generadorDeId = 0;
};

#endif //MAP_H
