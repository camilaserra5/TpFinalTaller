#ifndef KITS_MEDICOS_H
#define KITS_MEDICOS_H

#include "item.h"

class KitsMedicos : public Item {
public:
    KitsMedicos(Posicion &posicion);

    ~KitsMedicos();

    void obtenerBeneficio(ContenedorDeElementos &contenedor,Jugador *jugador) override;


private:
    int puntos_de_vida;
};

#endif
