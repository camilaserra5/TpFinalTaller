#include "../include/armaAnimada.h"
#include <config.h>

#define RUTAIMG IMGS_DIR WEAPONS_IMG
#define SPRITES_W 64.55
#define SPRITES_H 65
#define FRAMES_X 5
#define FRAMES_Y 4
#define POSX 318
#define POSY 420
#define CONTADOR_INICIAL 70

#define RUTA_SONIDO_CUCHILLO SOUNDS_DIR KNIFE_SOUND
#define RUTA_SONIDO_PISTOLA SOUNDS_DIR PISTOL_SOUND
#define RUTA_SONIDO_AMETRALLADORA SOUNDS_DIR AMETRALLADORA_SOUND
#define RUTA_SONIDO_CANION SOUNDS_DIR CANION_SOUND

#define ID_CUCHILLO 3
#define ID_PISTOLA 4
#define ID_AMETRALLADORA 1
#define ID_LANZACOHETES 5
#define ID_CANION_DE_CADENA 2

ArmaAnimada::ArmaAnimada(SDL_Renderer *render) : contador(CONTADOR_INICIAL), atacando(false) {
    //Audio audio;
    Sprite spriteCuchillo(render, RUTAIMG, 1, 0, SPRITES_H, SPRITES_W);
    Sprite spritePistola(render, RUTAIMG, 0, 1, SPRITES_H, SPRITES_W);
    Sprite spriteAmetralladora(render, RUTAIMG, 0, 2, SPRITES_H, SPRITES_W);
    Sprite spriteCanion(render, RUTAIMG, 0, 3, SPRITES_H, SPRITES_W);

    Animacion animacionCuchillo(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 0, -1);
    Animacion animacionPistola(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 1, -1);
    Animacion animacionAmetralladora(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 2, -1);
    Animacion animacionCanion(render, RUTAIMG, FRAMES_X, SPRITES_H, SPRITES_W, 3, -1);

    //Musica sonidoCuchillo(RUTA_SONIDO_CUCHILLO);
    //Musica sonidoPistola(RUTA_SONIDO_PISTOLA);
    //Musica sonidoAmetralladora(RUTA_SONIDO_AMETRALLADORA);
    //Musica sonidoCanion(RUTA_SONIDO_CANION);

    this->sprites.insert(std::make_pair(ID_CUCHILLO, spriteCuchillo));
    this->sprites.insert(std::make_pair(ID_PISTOLA, spritePistola));
    this->sprites.insert(std::make_pair(ID_AMETRALLADORA, spriteAmetralladora));
    this->sprites.insert(std::make_pair(ID_CANION_DE_CADENA, spriteCanion));

    this->animaciones.insert(std::make_pair(ID_CUCHILLO, animacionCuchillo));
    this->animaciones.insert(std::make_pair(ID_PISTOLA, animacionPistola));
    this->animaciones.insert(std::make_pair(ID_AMETRALLADORA, animacionAmetralladora));
    this->animaciones.insert(std::make_pair(ID_CANION_DE_CADENA, animacionCanion));

    //this->sonidos.insert(std::move(std::make_pair(ID_CUCHILLO, sonidoCuchillo)));
    //this->sonidos.insert(std::move(std::make_pair(ID_PISTOLA, sonidoPistola)));
    //this->sonidos.insert(std::move(std::make_pair(ID_AMETRALLADORA, sonidoAmetralladora)));
    //this->sonidos.insert(std::move(std::make_pair(ID_CANION_DE_CADENA, sonidoCanion)));

    this->armaActual = ID_PISTOLA;
}

ArmaAnimada::~ArmaAnimada() {}

void ArmaAnimada::actualizar(int armaActual, bool estado) {
    this->armaActual = armaActual;
    this->atacando = estado;
}

void ArmaAnimada::renderizar() {
    // Audio audio;
    if (this->atacando) {
    //    this->sonidos.find(this->armaActual)->second.play(-1);
        if (this->contador != 0) {
            std::cerr << "entre";
            this->animaciones.find(this->armaActual)->second.renderizar(POSX, POSY, 0, NULL);
            this->contador--;
        } else {
            this->contador = CONTADOR_INICIAL;
            this->atacando = false;
        }
    } else {
        this->sprites.find(armaActual)->second.renderizar(POSX, POSY, 0, NULL);
    }
}
