#ifndef LOGRO_H
#define LOGRO_H

#include "iserializable.h"

/*
Al finalizar la partida se deberá mostrar un top 5 de los jugadores con más enemigos matadas, más puntos
por tesoros y más balas disparadas
*/

class Logro : public ISerializable {
public:
    bool operator>(Logro &logro);

    bool operator==(Logro &logro);

    void aniadirBalasDisparadas(int cantidadDeBalas);

    void aniadirPuntosPorTesoro(int puntos);

    void aniadirEnemigosMatados(int cantidadDeEnemigos);

    std::vector<char> serializar() override;/* {
        std::vector<char> info;
        std::vector<char> aux(4);
        aux = numberToCharArray(this->enemigosMatados);
        info.insert(info.end(), aux.begin(), aux.end());

        aux = numberToCharArray(this->puntosTotalesPorTesoros);
        info.insert(info.end(), aux.begin(), aux.end());

        aux = numberToCharArray(this->balasDisparadas);
        info.insert(info.end(), aux.begin(), aux.end());
        return info;
    }*/

    void deserializar(std::vector<char> &serializado) override; /* {
        std::vector<char> sub(4);
        int idx = 0;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->enemigosMatados = charArrayToNumber(sub);

        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->puntosTotalesPorTesoros = charArrayToNumber(sub);

        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->balasDisparadas = charArrayToNumber(sub);
    }*/

    int obtenerPuntosTotales();

private:
    int enemigosMatados = 0;
    int puntosTotalesPorTesoros = 0; //no se si se acumula o deberia compararse uno por uno, sino decision de implementacion: se acumula
    int balasDisparadas = 0;
};

#endif
