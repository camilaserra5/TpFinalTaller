#ifndef CANION_DE_CADENA_H
#define CANION_DE_CADENA_H
#define DISTANCIA_MAX 2000000
#define TICKS_DISPARO_CANION 3

#include "arma.h"
#include "items/item.h"


class CanionDeCadena : public Arma, public Item {
public:
    /*
      * creara la clase canion de caneda dejandola valida para uso
    */
    CanionDeCadena(Posicion &posicion, int id, ConfiguracionPartida& configuracion);
    /*
      * liberara la clase con sus recursos
    */
    ~CanionDeCadena();
    /*
      * realizara el ataque. devuelve la actualizacion del ataque o null si no
      * puede atacar
    */
    Actualizacion *atacar(int distancia_a_pared, Jugador *jugador,
                          std::map<int, Jugador *> &jugadores) override;
    /*
      * devuelve true si pudo agarrar el arma o false en caso contrario
    */
    bool obtenerBeneficio(Jugador *jugador);
    /*
      * realiza el ataque efectivamente devolviendo la actualizacion correspondiente
    */
    Actualizacion *atacarEfectivamente(Jugador *jugador, std::map<int, Jugador *> &jugadores);
    /*
      * devuelve el tipo de arma
    */  
    Type getTipo() override;

private:
    double contador;
    ConfiguracionPartida configuracion;
};

#endif
