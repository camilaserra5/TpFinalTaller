#ifndef CONFIG_PARTIDA_H
#define CONFIG_PARTIDA_H

class ConfiguracionPartida{
    public:
      void setVRotacion(float vRotacion);
      void setVAvance(float vAvance);
      void setVidaMax(float vidaMax);
      void setBalasPorRafagaAmetralladora(int balasPorRafagaAmetralladora);
      void setBalasPorRafagaCanion(int balasPorRafagaCanion);
      void setMaxBalas(int maxBalas);
      void setCantidadBalasInicial(int cantidadBalasInicial);
      void setDistanciaMaxAcuchillable(float distanciaMaxAcuchillable);
      void setPuntos_cruz(float puntos_cruz);
      void setPunto_copa(float punto_copa);
      void setPunto_cofre(float punto_cofre);
      void setPuntos_corona(float puntos_corona);
      void setCantidadVidas(int cantidadVidas);
      int getBalasInicial();
      float getVRotacion();
      float getVidaMax();
      float obtenerVAvance();
    private:
      float vRotacion;
      float vAvance;
      float vidaMax;
      int balasPorRafagaAmetralladora;
      int balasPorRafagaCanion;
      int maxBalas;
      float cantidadBalasInicial;
      float distanciaMaxAcuchillable;
      float puntos_cruz;
      float puntos_copa;
      float puntos_cofre;
      float puntos_corona;
      int cantidadVidas;
};

#endif
