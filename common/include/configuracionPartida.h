#ifndef CONFIG_PARTIDA_H
#define CONFIG_PARTIDA_H

class ConfiguracionPartida {
public:
    /*settea la velocidad de rotacion a utilizar en el juego*/
    void setVRotacion(float vRotacion);

    /*settea la velocidad de avance a utilizar en el juego*/
    void setVAvance(float vAvance);

    /*settea la vida maxima a utilizar en el juego por el jugador*/
    void setVidaMax(float vidaMax);

    /*settea las balas por rafaga de la ametralladora utilizar en el juego*/
    void setBalasPorRafagaAmetralladora(int balasPorRafagaAmetralladora);

    /*settea las balas por rafaga del canion utilizar en el juego*/
    void setBalasPorRafagaCanion(int balasPorRafagaCanion);

    /*settea las balas por rafaga de la pistola utilizar en el juego*/
    void setBalasPorRafagaPistola(int balasPorRafagaPistola);

    /*settea la cantidad maxima de balas a utilizar en el juego por el jugador*/
    void setMaxBalas(int maxBalas);

    /*settea la cantidad de balas inicial a utilizar en el juego por el jugador*/
    void setCantidadBalasInicial(int cantidadBalasInicial);

    /*settea la maxima acuchillable a utilizar en el juego por el jugador*/
    void setDistanciaMaxAcuchillable(float distanciaMaxAcuchillable);

    /*settea la cantidad de puntos por tesoro cruz a utilizar en el juego*/
    void setPuntos_cruz(float puntos_cruz);

    /*settea la cantidad de puntos por tesoro copa a utilizar en el juego*/
    void setPunto_copa(float punto_copa);

    /*settea la cantidad de puntos por tesoro cofre a utilizar en el juego*/
    void setPunto_cofre(float punto_cofre);

    /*settea la cantidad de puntos por tesoro corona a utilizar en el juego*/
    void setPuntos_corona(float puntos_corona);

    /*settea la cantidad de vidas a utilizar en el juego por el jugador*/
    void setCantidadVidas(int cantidadVidas);

    /*settea la cantidad de puntos por balas a utilizar en el juego*/
    void setPuntosBalas(int puntosBalas);

    /*settea la cantidad de puntos por matar a utilizar en el juego*/
    void setPuntosMatar(int puntosMatar);

    /*devuelve la cantidad de balas a utilizar en el juego*/
    int getBalasInicial();

    /*devuelve la velocidad de rotacion en el juego*/
    float getVRotacion();

    /*devuelve la vida maxima a utilizar en el juego*/
    int getVidaMax();

    /*devuelve la velocidad de avance a utilizar en el juego*/
    float obtenerVAvance();

    /*devuelve la cantidad de vidas del jugador a utilizar en el juego*/
    int getCantidadDeVidas();

    /*devuelve la cantidad de puntos por tesoro de cruz a utilizar en el juego*/
    int getPuntosCruz();

    /*devuelve la cantidad de puntos por tesoro de copa a utilizar en el juego*/
    int getPuntosCopa();

    /*devuelve la cantidad de puntos por tesoro de cofre a utilizar en el juego*/
    int getPuntosCofre();

    /*devuelve la cantidad de puntos por tesoro de corona a utilizar en el juego*/
    int getPuntosCorona();

    /*devuelve la cantidad de puntos por balas a utilizar en el juego*/
    int getPuntosBalas();

    /*devuelve la cantidad max de balas a que puede tener el jugador a la vez a utilizar en el juego*/
    int getMaxBalas();

    /*devuelve la cantidad de puntos por matar*/
    int getPuntosMatar();

    /*devuelve danio maximo producido por el arma */
    int getDanioMaximoArma();

    /*devuelve las balas por rafaga de la ametralladora*/
    int getBalasPorRafagaAmetralladora();

    /*devuelve las balas por rafaga del canion*/
    int getBalasPorRafagaCanion();

    /*devuelve las balas por rafaga de la pistola*/
    int getBalasPorRafagaPistola();

    /*settea el danio maximo producido por un arma*/
    void setDanioMaximoArma(int danio_maximo_arma);

    /*devuelve los puntos de vida por comida*/
    int getPuntosVidaComida();

    /*devuelve la cantidad de balas en el mapa*/
    int getBalasEnMapa();

    /*devuelve los puntos de vida por kits medicos*/
    int getPuntosDeVidaKits();

    /*devuelve los puntos de vida por sangre*/
    int getPuntosDeVidaSangre();

    /*settea los puntos de vida por kits*/
    void setPuntosDeVidaKits(int puntosKits);

    /*settea los puntos de vida por sangre*/
    void setPuntosDeVidaSangre(int puntosSangre);

    /*settea los puntos de vida por comida*/
    void setPuntosVidaComida(int puntosVidaComida);

    /*settea la cantidad de balas en el mapa*/
    void setBalasEnMapa(int balasEnMapa);

private:
    float vRotacion;
    float vAvance;
    int vidaMax;
    int balasPorRafagaAmetralladora;
    int balasPorRafagaCanion;
    int balasPorRafagaPistola;
    int maxBalas;
    float cantidadBalasInicial;
    float distanciaMaxAcuchillable;
    float puntosCruz;
    float puntosCopa;
    float puntosCofre;
    float puntosCorona;
    int cantidadVidas;
    int puntosMatar;
    int puntosBalas;
    int danio_maximo_arma;
    int puntosVidaComida;
    int balasEnMapa;
    int puntosVidaKits;
    int puntosVidaSangre;
};

#endif
