#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <iostream>
#include "objetosJuego.h"
#include <sstream>
#include <vector>
#include <cstring>
#include <netinet/in.h>

class ISerializable {
public:
    virtual std::vector<char> serializar() = 0;

    virtual void deserializar(std::vector<char> &serializado) = 0;

    virtual ~ISerializable() {}

    std::vector<char> numberToCharArray(uint32_t number) {
        std::vector<char> ret(4);
        unsigned int size = htonl(number);
        memcpy(ret.data(), &size, 4);
        return ret;
    }

    uint32_t charArrayToNumber(std::vector<char> array) {
        char number[4];
        memcpy(number, array.data(), 4);
        uint32_t *buf = (uint32_t *) number;
        return ntohl(*buf);
    }
};

#endif
