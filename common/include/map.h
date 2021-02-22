#ifndef MAP_H
#define MAP_H

#include <vector>
#include "contenedorDeElementos.h"
#include "items/item.h"
#include "objetosJuego.h"
#include "iserializable.h"
#include <iostream>
#include "puerta.h"
#include "configuracionPartida.h"


class Map : public ISerializable {
public:
//largo preconcatenado
   /*
     * crearar la clase mapa dejandola valida para uso
     * sus parametros debene ser validos
    */
    Map(unsigned rowSize, unsigned colSize, int anchoPantalla,
        ConfiguracionPartida& configuracion);
    /*
      * devuelve la cantidad de filas
    */
    unsigned getRowSize() const;
    /*
      * devuelve la cantidad de columnas
    */
    unsigned getColSize() const;
    /*
      * settea el valor que le llega en la posicon correspndiente
    */
    void setValue(const unsigned rowNumber, const unsigned colNumber,
                  Type value);
    /*
      * implemneta el operador (); devuelve el tipo de lo que hay en
      * esa fila y columna
    */
    Type &operator()(const unsigned rowNumber, const unsigned colNumber);
    /*
      * crea el elemnto en una posicion random dentr de su celda
    */
    void crearElementoPosicionable(const unsigned rowNumber,
                                    const unsigned colSize, Type value);
    /*
      * busca el elemnto en es aposicion y lo devuelve, si no esta
      * devuelve null
    */
    Item *buscarElemento(int &posx, int &posy);
    /*
      * devuelve el contendor de elementos
    */
    ContenedorDeElementos &obtenerContenedor();
    /*
      * saca al objeto de esa posicion del mapa
    */
    void sacarDelMapa(Posicion &posicion);
    /*
      * liberara la clase con todos sus recursos
    */
    ~Map();
    /*
      * agrega el elemento en el contendor
    */
    void agregarElemento(Item *item);
    /*
      * agrega una puerta en el contendor
    */
    void aniadirPuerta(const unsigned rowNumber, const unsigned colNumber, int tipoPuerta);
    /*
      * serializa la clase devolviendo su informacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializa la clase, poniendo sus valores previos
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * devuelve el vector de items
    */
    std::vector<Item *> &obtenerItems();
    /*
      * devuelve la puerta mas cercana
    */
    Puerta &puertaMasCercana(Posicion &posicionJugador, double &distancia);
    /*
      * devuelve true si hay puertas
    */
    bool hayPuertas();
    /*
      * agrega un arma al contenedor de elemntos
    */
    void agregarArma(Posicion &posicion, Arma *arma);
    /*
      * crea un id valido
    */
    int crearIdValido();
    /*
      * devuelve true si hay colicion sino no
    */
    bool hayColision(int fila, int columna);
    /*
      * devuelve una posicon inicial valida
    */
    Posicion obtenerPosicionInicialValida();
    /*
      * constrcutor por default
    */
    Map() {}
    /*
      * settea el lado de la celd
    */
    void setLadoCelda(int anchoPantalla);
    /*
      *devuelve el lado de la celda
    */
    int getLadoCelda();
    /*
      * devuelve el mapa de numeros
    */
    std::vector<std::vector<int>> getMapanumerico();
    /*
      * operador por movimiento
    */
    Map(Map&& mapa);
    /*
      * operador = por movimiento
    */  
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
    ContenedorDeElementos *contenedorDeElementos = NULL;
    std::vector<std::vector<Type>> map;
    std::vector<int> idCargados;
    int ladoCelda;
    int generadorDeId = 0;
    ConfiguracionPartida configuracion;
};

#endif //MAP_H
