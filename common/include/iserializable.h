#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

class ISerializable {
public:
    virtual /*std::stringstream*/void serializar() = 0;

    virtual void deserializar(/*std::stringstream secuencia*/) = 0;

    virtual ~ISerializable() {}
};

#endif
