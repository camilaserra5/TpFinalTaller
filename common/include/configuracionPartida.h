#ifndef CONFIG_PARTIDA_H
#define CONFIG_PARTIDA_H

class ConfiguracionPartida {
public:
    void setVRotacion(float vRotacion);

    void setVAvance(float vAvance);

    void setVidaMax(float vidaMax);

    void setBalasPorRafagaAmetralladora(int balasPorRafagaAmetralladora);

    void setBalasPorRafagaCanion(int balasPorRafagaCanion);

    void setBalasPorRafagaPistola(int balasPorRafagaPistola);

    void setMaxBalas(int maxBalas);

    void setCantidadBalasInicial(int cantidadBalasInicial);

    void setDistanciaMaxAcuchillable(float distanciaMaxAcuchillable);

    void setPuntos_cruz(float puntos_cruz);

    void setPunto_copa(float punto_copa);

    void setPunto_cofre(float punto_cofre);

    void setPuntos_corona(float puntos_corona);

    void setCantidadVidas(int cantidadVidas);

    void setPuntosBalas(int puntosBalas);

    void setPuntosMatar(int puntosMatar);

    int getBalasInicial();

    float getVRotacion();

    int getVidaMax();

    float obtenerVAvance();

    int getCantidadDeVidas();

    int getPuntosCruz();

    int getPuntosCopa();

    int getPuntosCofre();

    int getPuntosCorona();

    int getPuntosBalas();

    int getPuntosMatar();

    int getDanioMaximoArma();

    int getBalasPorRafagaAmetralladora();

    int getBalasPorRafagaCanion();

    int getBalasPorRafagaPistola();

    void setDanioMaximoArma(int danio_maximo_arma);

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
};

#endif
