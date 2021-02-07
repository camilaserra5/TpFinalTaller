
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

    std::vector<char> serializar() override; /* {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(elementos.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        for (auto &elemento : elementos) {
            std::vector<char> itemSerializado = ((Item *) elemento)->serializar();
            aux = numberToCharArray(itemSerializado.size());
            informacion.insert(informacion.end(), aux.begin(), aux.end());
            informacion.insert(informacion.end(), itemSerializado.begin(), itemSerializado.end());
        }
        return informacion;
    }*/

    void deserializar(std::vector<char> &serializado) override; /* {
        std::vector<char> sub(4);
        int idx = 0;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        int elementosSize = charArrayToNumber(sub);
        idx += 4;
        for (int i = 0; i < elementosSize; i++) {
            sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
            idx += 4;
            std::vector<char> itemSerializado(serializado.begin() + idx,
                                              serializado.begin() + idx + charArrayToNumber(sub));
            idx += charArrayToNumber(sub);
            Item *item;
            item->deserializar(itemSerializado);
            this->elementos.push_back(item);
        }
    }*/

    std::vector<Item *> &obtenerItems(); /* {
        return this->elementos;
    }*/


    bool hayPuertas();

    Puerta &puertaMasCercana(Posicion &posicionJugador, double &distancia);

    Puerta &obtenerPuertaEn(int &fila, int &columna);

    void aniadirPuerta(Puerta& puerta);

private:
    std::vector<Item *> elementos;
    std::vector<Puerta> puertas;
};

#endif
