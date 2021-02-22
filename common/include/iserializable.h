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
    /*
      * serializa la clase devolviendo su informacion
    */
    virtual std::vector<char> serializar() = 0;
    /*
      * deserializa la clase dejandola en su estado previo
    */
    virtual void deserializar(std::vector<char> &serializado) = 0;
    /*
      * libera la clase con sus recursos
    */
    virtual ~ISerializable() {}
    /*
      * combierte el numero a un vector de char
    */
    std::vector<char> numberToCharArray(uint32_t number) {
        std::vector<char> ret(4);
        unsigned int size = htonl(number);
        memcpy(ret.data(), &size, 4);
        return ret;
    }
    /*
      * convierte el vector de chars a uint32
    */  
    uint32_t charArrayToNumber(std::vector<char> array) {
        char number[4];
        memcpy(number, array.data(), 4);
        uint32_t *buf = (uint32_t *) number;
        return ntohl(*buf);
    }
};

#endif
