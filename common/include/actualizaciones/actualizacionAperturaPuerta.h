#ifndef ACTUALIZACION_PUERTA_H
#define ACTUALIZACION_PUERTA_H


#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"
#include "puerta.h"

class ActualizacionAperturaPuerta : public Actualizacion {
public:
    /*
      * creara la actualizacion apertura de prueba dejandola valida
    */
    ActualizacionAperturaPuerta(Puerta &puerta);

    /*
      * constructor por default
    */
    ActualizacionAperturaPuerta() {}

    /*
      * liberara la apertura de puertas
    */
    ~ActualizacionAperturaPuerta();
    /*
      * serializa la actualizacion y devuelve la informacion
    */
    std::vector<char> serializar() override;
    /*
      * deserializa la clase, dejandola en sus valores correspondientes
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * devuelve el id Correspondiente
    */  
    int obtenerId() override { return static_cast<int>(Accion::aperturaDePuerta); }

private:
    Puerta puerta;
};

#endif
