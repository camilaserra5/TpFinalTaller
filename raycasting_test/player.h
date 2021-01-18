#ifndef _PLAYER_H
#define _PLAYER_H

// no se si es un sprite;
// falta ver tema imagen/arma

class Player{
    public:
        Player(const char* rutaimg, SDL_Renderer* render, int id):
        posx(0),
        posy(0),
        vida(100),
        anguglo(50),
        id(id),
        ObjetoJuego(rutaimg, render, posx, posy, 10, 10){}

        ~Player();
        void settear_estado(int posx, int posy, int vida, int angulo){
            this->posx = posx;
            this->posy = posy;
            this->vida = vida;
            this->angulo = angulo;
            this->objetoDibujable.actualizar(posx, posy);
        }
        void renderizar(){
            this->objetoDibujable.renderizar();
        }
    private:
      int posx;
      int posy;
      int vida;
      int angulo;
      int id;
      ObjetoJuego objetoDibujable;
};

#endif
