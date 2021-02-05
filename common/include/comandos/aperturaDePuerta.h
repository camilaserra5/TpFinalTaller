#ifndef __APERTURA_DE_PUERTA__
#define __APERTURA_DE_PUERTA__

#include "comandos/comando.h"

class AperturaDePuerta : public Comando {

public:
    AperturaDePuerta(int idJugador);

    ~AperturaDePuerta();

    void ejecutar(EstadoJuego &estadoJuego) override;

    std::vector<char> serializar() override;/* {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(idJugador);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        aux = numberToCharArray(static_cast<int>(Accion::aperturaDePuerta));
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        return informacion;
    }*/

    void deserializar(std::vector<char> &serializado) override;/*{
        std::vector<char> sub(4);
        int idx = 0;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->idJugador = charArrayToNumber(sub);
    }*/

};


#endif
