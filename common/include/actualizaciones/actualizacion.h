#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H


#include <list>
#include "iserializable.h"
#include "ranking.h"


class Actualizacion : public ISerializable {
public:
    /*
      * creara la actualizacion dejandola valida para uso
    */
    Actualizacion();

    /*
      * liberara la actualizacion con sus recursos
    */
    ~Actualizacion();

    /*
      * devuelve el id de la actualizacion
    */
    virtual int obtenerId() = 0;

private:
};

#endif
