#ifndef LOGRO_H
#define LOGRO_H

#include "iserializable.h"
#include "configuracionPartida.h"
/*
Al finalizar la partida se deberá mostrar un top 5 de los jugadores con más enemigos matadas, más puntos
por tesoros y más balas disparadas
*/

class Logro : public ISerializable {
public:
    /*
      * creara la clase logro dejandola valida para uso
    */
    Logro(ConfiguracionPartida& configuracion): puntosBalas(configuracion.getPuntosBalas()),
                                                puntosMatar(configuracion.getPuntosMatar()){}
    /*
      * constructor por defautl
    */
    Logro();
    /*
      * operador >
    */
    bool operator>(Logro &logro);
    /*
      * operador ==
    */
    bool operator==(Logro &logro);
    /*
      * agrego balas disparadas
    */
    void aniadirBalasDisparadas(int cantidadDeBalas);
    /*
      * agrego puntos pos tersosor
    */
    void aniadirPuntosPorTesoro(int puntos);
    /*
      * agrego enemigos matados
    */
    void aniadirEnemigosMatados(int cantidadDeEnemigos);
    /*
      * seriliza la clase devolvuneod la informacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializa la clase poniendole sus valores previos
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * devuelve los puntos puntosTotales
    */
    int obtenerPuntosTotales();
    /*
      * devuelve enemigos matados
    */
    int obtenerEnemigosMatados() { return enemigosMatados; }
    /*
      * dvuelves puntos por tesoro
    */
    int obtenerPuntosTotalesPorTesoros() { return puntosTotalesPorTesoros; }
    /*
      * devuelve las balas disparadas
    */
    int obtenerBalasDisparadas() { return balasDisparadas; }

private:
    int enemigosMatados = 0;
    int puntosTotalesPorTesoros = 0; //no se si se acumula o deberia compararse uno por uno, sino decision de implementacion: se acumula
    int balasDisparadas = 0;
    int puntosBalas;
    int puntosMatar;
};

#endif
