
#ifndef CONTENEDOR_DE_ELEMENTOS
#define CONTENEDOR_DE_ELEMENTOS

#include <vector>
#include "puerta.h"
#include "items/item.h"
#include "items/comida.h"
#include "items/balas.h"
#include "items/sangre.h"
#include "items/kitsMedicos.h"
#include "items/noItem.h"
#include "items/llave.h"
#include "items/tesoro.h"
#include "armas/canionDeCadena.h"
#include "armas/ametralladora.h"
#include "iserializable.h"
#include <string>

class ContenedorDeElementos : public ISerializable {

public:
    ContenedorDeElementos();

    ~ContenedorDeElementos();

    void agregarElemento(Item *elemento);

    void sacarElementoDePosicion(Posicion &posicion);

    Item *buscarElemento(int &pox, int &posy);

    std::vector<char> serializar() override {
        std::vector<char> informacion;
        informacion.push_back(elementos.size());
        for (auto &elemento : elementos) {
            std::vector<char> itemSerializado = ((Item *) elemento)->serializar();
            informacion.insert(informacion.end(), itemSerializado.begin(), itemSerializado.end());
        }
        return informacion;
    }

    void deserializar(std::vector<char>& serializado) override {
        char size = serializado[0];

        int ult = 1;
        for (int i = 0; i < size; i++) {
            std::vector<char> itemSerializado(serializado.begin() + ult,
                                              serializado.begin() + ult + 2);
            Item *item;
            item->deserializar(itemSerializado);
            this->elementos.push_back(item);
            ult = ult + 2;
        }
    }

    bool hayPuertas();

    Puerta& puertaMasCercana(Posicion& posicionJugador,double& distancia);
private:
    std::vector<Item*> elementos;
    std::vector<Puerta> puertas;
};

#endif
