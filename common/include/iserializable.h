#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <iostream>
#include "objetosJuego.h"
#include <sstream>
#include <vector>
class ISerializable {
public:
    virtual std::vector<char> serializar() = 0;

    virtual void deserializar(std::vector<char> serializado) = 0;

    virtual ~ISerializable() {}
};

#endif
