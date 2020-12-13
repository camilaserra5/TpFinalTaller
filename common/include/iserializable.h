#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

class ISerializable {
public:
    virtual void serializar() = 0;

    virtual void deserializar() = 0;

    virtual ~ISerializable() {}
};

#endif
