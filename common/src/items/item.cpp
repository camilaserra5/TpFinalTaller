#include "../include/items/item.h"

Item::Item(Posicion &posicion, int id) : posicion(posicion), id(id) {}

Item::Item() {}


bool Item::estaCerca(int &posx, int &posy, float radio) {
    return this->posicion.estaCerca(posx, posy, radio);
}

Posicion Item::obtenerPosicion() {
    return this->posicion;
}

std::vector<char> Item::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->id);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->getTipo().getType());
    //std::cerr << "serializo\n";
    //std::cerr << "tipoid: " << this->getTipo().getType() << "\n";
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    std::vector<char> posicionSerializado = this->posicion.serializar();
    informacion.insert(informacion.end(), posicionSerializado.begin(),
                       posicionSerializado.end());
    return informacion;
}

void Item::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->id = charArrayToNumber(sub);
    idx += 4;
    std::vector<char> posicionSerializado(serializado.begin() + idx,
                                          serializado.end());
    this->posicion.deserializar(posicionSerializado);
}

int Item::getId() {
    return this->id;
}


Posicion &Item::getPosicion() {
    return this->posicion;
}
