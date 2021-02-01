#ifndef LOGRO_H
#define LOGRO_H

/*
Al finalizar la partida se deberá mostrar un top 5 de los jugadores con más enemigos matadas, más puntos
por tesoros y más balas disparadas
*/

class Logro {
public:
    bool operator>(Logro &logro);

    bool operator==(Logro &logro);

    void aniadirBalasDisparadas(int cantidadDeBalas);

    void aniadirPuntosPorTesoro(int puntos); //cada tesoro sabe cuantos puntos
    void aniadirEnemigosMatados(int cantidadDeEnemigos);

    int obtener_puntaje(){
        return puntosTotalesPorTesoros;
    }

private:
    int enemigosMatados = 0;
    int puntosTotalesPorTesoros = 0; //no se si se acumula o deberia compararse uno por uno, sino decision de implementacion: se acumula
    int balasDisparadas = 0;
};

#endif
