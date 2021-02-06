#include "../include/map.h"
#include <iostream>
#include "items/item.h"
#include "armas/arma.h"
#include "items/comida.h"
#include "items/balas.h"
#include "items/sangre.h"
#include "items/kitsMedicos.h"
#include "items/noItem.h"
#include "items/llave.h"
#include "items/tesoro.h"
#include "armas/canionDeCadena.h"
#include "armas/ametralladora.h"
#include "armas/lanzacohetes.h"
#include <algorithm>

#define TAM_CELDA 50
#define PUNTOS_CRUZ 10
#define PUNTOS_COPA 50
#define PUNTOS_COFRE 100
#define PUNTOS_CORONA 200
#define ANGULO_DEFAULT 0

void Map::agregarArma(Posicion &posicion, Arma *arma) {
    Type tipo = arma->getTipo();
    if (tipo.getName() == "ametralladora") {
        Item *ametralladora = new Ametralladora(posicion, arma->getId());
        this->contenedorDeElementos.agregarElemento(ametralladora);
    } else if (tipo.getName() == "canionDeCadena") {
        Item *canion = new CanionDeCadena(posicion, arma->getId());
        this->contenedorDeElementos.agregarElemento(canion);
    } else if (tipo.getName() == "lanzaCohetes") {
        Item *lanzaCohetes = new LanzaCohetes(posicion, arma->getId());
        this->contenedorDeElementos.agregarElemento(lanzaCohetes);
    }
}

void Map::sacarDelMapa(Posicion &posicion) {
    this->contenedorDeElementos.sacarElementoDePosicion(posicion);
}

Map::Map(unsigned rowSize, unsigned colSize) : contenedorDeElementos() {
    if (rowSize < 1 || colSize < 1) {
        throw std::runtime_error("Invalid map");
    }

    this->rowSize = rowSize;
    this->colSize = colSize;
    map.resize(rowSize);
    for (unsigned i = 0; i < map.size(); i++) {
        map[i].resize(colSize, ObjetosJuego::obtenerTipoPorNombre("empty"));
    }
}

unsigned Map::getRowSize() const {
    return this->rowSize;
}

unsigned Map::getColSize() const {
    return this->colSize;
}

int Map::crearIdValido() {
  int idValido = this->generadorDeId;
  this->generadorDeId ++;
  return idValido;
}

// pre condicion: va a ver un item por celda por facilidad, ya que sino se pisan;
void Map::crearElementoPosicionable(const unsigned rowNumber, const unsigned colNumber,
                                    Type value) {
    srand(time(NULL));
    std::cerr << " hola " << std::endl;
    int posElementox = 0;
    int posElementoy = 0;
    if (rowNumber == 0) {
        posElementox = (rowNumber * TAM_CELDA + rand() % ((1 + rowNumber) * TAM_CELDA));
    } else if (colNumber == 0) {
        int posElementoy = (colNumber * TAM_CELDA + rand() % ((1 + rowNumber) * TAM_CELDA));
    } else {
        posElementox = (rowNumber * TAM_CELDA + rand() % ((1 + rowNumber) * TAM_CELDA - rowNumber * TAM_CELDA));
        posElementoy = (colNumber * TAM_CELDA + rand() % ((1 + colNumber) * TAM_CELDA - colNumber * TAM_CELDA));
        std::cerr << " hola " << posElementox << std::endl;
        std::cerr << " hola " << posElementoy << std::endl;
    }
    Posicion posicion = Posicion(posElementox, posElementoy, 0);
    if (value.getName() == "comida") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Comida(posicion, idValido));
    } else if (value.getName() == "sangre") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Sangre(posicion, idValido));
    } else if (value.getName() == "kitsMedicos") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new KitsMedicos(posicion, idValido));
    } else if (value.getName() == "balas") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Balas(posicion, BALAS, idValido));
    } else if (value.getName() == "ametralladora") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Ametralladora(posicion, idValido));
    } else if (value.getName() == "canionDeCadena") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new CanionDeCadena(posicion, idValido));
    } else if (value.getName() == "lanzaCohetes") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new LanzaCohetes(posicion, idValido));
    } else if (value.getName() == "cruz") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(
                new Tesoro(idValido, ObjetosJuego::obtenerTipoPorNombre("cruz"), PUNTOS_CRUZ, posicion));
    } else if (value.getName() == "copa") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(
                new Tesoro(idValido, ObjetosJuego::obtenerTipoPorNombre("copa"), PUNTOS_COPA, posicion));
    } else if (value.getName() == "cofre") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(
                new Tesoro(idValido, ObjetosJuego::obtenerTipoPorNombre("cofre"), PUNTOS_COFRE, posicion));
    } else if (value.getName() == "corona") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(
                new Tesoro(idValido, ObjetosJuego::obtenerTipoPorNombre("corona"), PUNTOS_CORONA, posicion));
    } else if (value.getName() == "llave") {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Llave(posicion, idValido));
    } else {
        std::cerr << " id pre " <<  std::endl;
        int idValido = this->crearIdValido();
        std::cerr << " id pós " <<  std::endl;
        this->contenedorDeElementos.agregarElemento(new NoItem(posicion, idValido));
        std::cerr << " id pós pós " <<  std::endl;
    }

}

void Map::agregarElemento(Item *item) {
    this->agregarElemento(item);
}

Item *Map::buscarElemento(int &posx, int &posy) {
    return this->contenedorDeElementos.buscarElemento(posx, posy);
}

void Map::setValue(const unsigned rowNumber, const unsigned colNumber, Type value) {
    this->map[rowNumber][colNumber] = value;
    std::cerr << " hola " << std::endl;
    this->crearElementoPosicionable(rowNumber, colNumber, value);
}

Type &Map::operator()(const unsigned rowNumber, const unsigned colNumber) {
    return this->map[rowNumber][colNumber];
}

Map::~Map() {

}

bool Map::hayPuertas() {
    return this->contenedorDeElementos.hayPuertas();
}

Puerta &Map::puertaMasCercana(Posicion &posicionJugador, double &distancia) {
    return this->contenedorDeElementos.puertaMasCercana(posicionJugador, distancia);

}

std::vector<char> Map::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->rowSize);
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    aux = numberToCharArray(this->colSize);
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    for (unsigned i = 0; i < rowSize; i++) {
        for (unsigned j = 0; j < colSize; j++) {
            informacion.push_back((map[i][j]).getType());
        }
    }

    std::vector<char> contenedorSerializado = this->contenedorDeElementos.serializar();
    informacion.insert(informacion.end(), contenedorSerializado.begin(), contenedorSerializado.end());
    return informacion;
}

void Map::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->rowSize = charArrayToNumber(sub);

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->colSize = charArrayToNumber(sub);

    for (unsigned i = 0; i < rowSize; i++) {
        for (unsigned j = 0; j < colSize; j++) {
            idx += 4;
            sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
            setValue(i, j, ObjetosJuego::obtenerTipoPorId(charArrayToNumber(sub)));
        }
    }

    idx += 4;
    std::vector<char> contenedorDeElementosSerializado(serializado.begin() + idx, serializado.end());
    this->contenedorDeElementos.deserializar(contenedorDeElementosSerializado);
}

std::vector<Item *> &Map::obtenerItems() {
    return this->contenedorDeElementos.obtenerItems();
}

ContenedorDeElementos &Map::obtenerContenedor() {
    return this->contenedorDeElementos;
};

bool Map::hayColision(int fila, int columna) {
    //chequear si en caso de haber una puerta, si esta abierta y agregarle a la puerta el atributo exacto de la pos en el mapa
    // a la puerta le falta el contador para q se cierre
    int tipo = this->map[fila][columna].getType();
    if (tipo == TYPE_DOOR) {
        Puerta &puerta = this->contenedorDeElementos.obtenerPuertaEn(fila, columna);
        if (puerta.estaAbierta()) {
            tipo = TYPE_EMPTY;
        }
    }
    return (tipo != TYPE_EMPTY);
}

Posicion Map::obtenerPosicionIncialValida() {
    bool posEsValida = false;
    int posX, posY;
    srand(time(NULL));
    while (!posEsValida) {
        posX = rand() % this->rowSize;
        posY = rand() % this->colSize;
        if (!this->hayColision(posX, posY)) posEsValida = true;
    }
    posX *= this->ladoCelda;
    posY *= this->ladoCelda;
    Posicion posicion(posX, posY, ANGULO_DEFAULT);
    return posicion;
}
