#ifndef _JUGADOR_H
#define _JUGADOR_H

#include <vector>
#include <string>
#include "posicion.h"
#include "logro.h"
#include <map>
#include "iserializable.h"


class Arma;

class Jugador : public ISerializable {
public:
    Jugador(std::string &nombre, int &id);

    ~Jugador();

    Jugador();

    void moverse(int posx, int posy);

    void rotar(int sentido);

    void actualizar_vida(int &vidaActualizada);

    void agregar_item();

    void agregar_arma(Arma *arma);

    int cantidad_balas();

    int puntos_de_vida();

    void agregar_balas(int &balas);

    int posEnX();

    int posEnY();

    int getId();

    void setPosicion(Posicion &posicion);

    Posicion &getPosicion();

    Arma *getArma();

    float getAnguloDeVista();

    void actualizarArma();

    //void setAnguloDeVista(float anguloJugador){this->angulo = anguloJugador; }

    bool tengollave();

    void usarLlave();

    bool estaMuerto();

    bool poseeArma(Arma *arma);

    void agarrarLlave();

    void sumarPuntos(int puntos);

    void gastarBalas(int cantidadDeBalas);

    Logro &obtenerLogro();

    void aniadirEnemigosMatados(int jugadoresMatados);

    bool estaDisparando();

    void actualizarNuevaVida();

    int cant_de_vida();

    int obtenerPuntosTotales();

    std::vector<char> serializar() override; /* {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(this->id);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        aux = numberToCharArray(this->vida);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        aux = numberToCharArray(this->armaActual);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        aux = numberToCharArray(this->disparando);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        aux = numberToCharArray(this->cantidad_vidas);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        aux = numberToCharArray(this->balas);
        informacion.insert(informacion.end(), aux.begin(), aux.end());

        std::vector<char> posicionSerializado = this->posicion.serializar();
        aux = numberToCharArray(posicionSerializado.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        informacion.insert(informacion.end(), posicionSerializado.begin(), posicionSerializado.end());

        std::vector<char> logroSerializado = this->logro.serializar();
        aux = numberToCharArray(logroSerializado.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        informacion.insert(informacion.end(), logroSerializado.begin(), logroSerializado.end());


        return informacion;
    }*/
    
    void deserializar(std::vector<char> &serializado) override; /* {
        std::vector<char> sub(4);
        int idx = 0;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->id = charArrayToNumber(sub);
        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->vida = charArrayToNumber(sub);
        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->armaActual = charArrayToNumber(sub);
        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->disparando = charArrayToNumber(sub);
        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->cantidad_vidas = charArrayToNumber(sub);
        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->balas = charArrayToNumber(sub);

        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        std::vector<char> posicionSerializado(serializado.begin() + idx,
                                              serializado.begin() + idx + charArrayToNumber(sub));
        this->posicion.deserializar(posicionSerializado);

        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        std::vector<char> logroSerializado(serializado.begin() + idx,
                                           serializado.begin() + idx + charArrayToNumber(sub));
        this->logro.deserializar(logroSerializado);
    }
*/
private:
    Posicion posicion;
    int id;
    std::string nombre;
    int vida;
    std::map<int, Arma *> armas;
    int balas;
    float velocidadDeRotacion;
    int armaActual;
    int llaves;
    int cantidad_vidas;
    Logro logro;
    bool disparando;
};

#endif
