#ifndef _PLAYER_H
#define _PLAYER_H

// no se si es un sprite;
// falta ver tema imagen/arma
#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include "informacionJugador.h"

class Player{
    public:
<<<<<<< HEAD
        Player(const char* rutaimg, SDL_Renderer* render, int id):
        posx(0), posy(0), vida(100),nivel(1), puntaje(100), angulo(50), id(id),
        infoJugador(render, vida,nivel, puntaje){
            Sprite spriteCuchillo = Sprite(render, rutaimg, 1, 0, 65, 60);
            Sprite spritePistola = Sprite(render, rutaimg, 0, 1, 65, 60);
            Sprite spriteAmetralladora = Sprite(render, rutaimg, 0, 2, 65, 60);
            Sprite spriteCanion = Sprite(render, rutaimg, 0, 3, 65, 60);
            this->sprites.insert(std::make_pair("cuchillo", spriteCuchillo));
            this->sprites.insert(std::make_pair("pistola", spritePistola));
            this->sprites.insert(std::make_pair("ametralladora", spriteAmetralladora));
            this->sprites.insert(std::make_pair("canion", spriteCanion));
        }

        ~Player();
        // actualizacion
        void settear_estado(int posx, int posy, int vida, int angulo){
            this->posx = posx;
            this->posy = posy;
            this->vida = vida;
            this->angulo = angulo;
            this->infoJugador.actualizarDatosJugador(vida, nivel, puntaje);
        }
        void renderizar(){
            this->sprites.find("pistola")->second.renderizar(this->posx, this->posy, this->angulo);
            this->infoJugador.renderizar();

        }
=======
        Player(const char* rutaimg, SDL_Renderer* render, int id);

        ~Player();
        // actualizacion
        void settear_estado(int posx, int posy, int vida, int angulo);
        void renderizar();

>>>>>>> d736525b05b728bc0dd858bb4c0f59e77974ade9
    private:
      int posx;
      int posy;
      int vida;
      int nivel;
      int puntaje;
      int angulo;
      int id;
      InfoJugador infoJugador;
      std::map<std::string, Sprite> sprites;
};

#endif
