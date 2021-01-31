#include "../include/armaAnimada.h"

#define RUTAIMG "../../client/resources/images/Weapons.png"
#define SPRITES_W 64.55
#define SPRITES_H 64.2
#define FRAMES_X 5
#define FRAMES_Y 4
#define POSX 318
#define POSY 420

ArmaAnimada::ArmaAnimada(SDL_Renderer* render){
      Sprite spriteCuchillo(render, RUTAIMG, 1, 0, SPRITES_W, SPRITES_H);
      Sprite spritePistola(render, RUTAIMG, 0, 1, SPRITES_W, SPRITES_H);
      Sprite spriteAmetralladora(render, RUTAIMG, 0, 2, SPRITES_W, SPRITES_H);
      Sprite spriteCanion(render, RUTAIMG, 0, 3, SPRITES_W, SPRITES_H);
      Animacion animacionCuchillo(render, RUTAIMG, FRAMES_X,SPRITES_H, SPRITES_W, 0, -1);
      Animacion animacionPistola(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 1, -1);
      Animacion animacionAmetralladora(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 2, -1);
      Animacion animacionCanion(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 3, -1);
      this->sprites.insert(std::make_pair(3, spriteCuchillo));
      this->sprites.insert(std::make_pair(4, spritePistola));
      this->sprites.insert(std::make_pair(1, spriteAmetralladora));
      this->sprites.insert(std::make_pair(2, spriteCanion));
      this->animaciones.insert(std::make_pair(3,animacionCuchillo));
      this->animaciones.insert(std::make_pair(4,animacionPistola));
      this->animaciones.insert(std::make_pair(1,animacionAmetralladora));
      this->animaciones.insert(std::make_pair(2,animacionCanion));
      this->armaActual = 4;
}

ArmaAnimada::~ArmaAnimada(){}

void ArmaAnimada::actualizar(int armaActual){
    this->armaActual = armaActual;
}

void ArmaAnimada::renderizar(bool& disparando){
      if(disparando){
            bool termine = this->animaciones.find(this->armaActual)->second.renderizar(POSX, POSY, 0, NULL);
            //termine ? this->disparando = false: this->disparando = true;

      } else {
          this->sprites.find(this->armaActual)->second.reescalar(2, 2);
          this->sprites.find(this->armaActual)->second.renderizar(POSX, POSY, 0, NULL);
      }

}
