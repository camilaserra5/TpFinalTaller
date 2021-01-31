#include "../include/modelo.h"
#include <iostream>

#define SPRITES_OBJETOS_ANCHO 320
#define SPRITES_OBJETOS_LARGO 650
#define SPRITE_OBJETOS "../../client/resourses/images/Objects.png,"
#define FRAMESX 5
#define FRAMESY 10

Modelo::Modelo(Ventana *ventana, int idJugador) :
        ventana(ventana),
        idJugador(idJugador),
        jugador(),
        enemigos(),
        entidades(),
        x(0){}

Modelo::~Modelo() {}

void Modelo::inicializar() {
    this->jugador = new Player("../../client/resources/images/Weapons.png", this->ventana->obtener_render(),
                                this->idJugador);
    int armaJugador(4);
    Enemigo* enemigo = new Enemigo(this->ventana->obtener_render(), armaJugador);
    this->enemigos.push_back(enemigo);

}

void Modelo::renderizar() {
  int posx(318),posy(420),vida(100),angulo(50),idArma(4);
    this->jugador->settear_estado(posx, posy, vida, angulo, idArma);
    this->jugador->renderizar();
    // verificar items si estan en posicion;
    // verificar enemigos si estan en posicion correcta;
    
    for (int i=0; i<this->enemigos.size(); i++){
      int posx(500), posy(300),idArma(4),anguloEnemigo(0),anguloJugador(90),vida(100);
          this->enemigos[i]->actualizar(posx, posy, idArma, anguloEnemigo, anguloJugador, vida);
          this->enemigos[i]->renderizar();
    }


    //jugador->dejarDeDisparar();

}

void Modelo::actualizarObjeto(int id, Type tipo, int posx, int posy) {

    if (entidades[id] == NULL) {
        ObjetoJuego *objeto = this->crearObjeto(tipo);
        this->entidades[id] = objeto;
    }
    this->entidades[id]->settear_estado(posx, posy);

}

void Modelo::actualizarJugador(int x, int y, int vida, int angulo, int id, int arma) {
    this->jugador->settear_estado(x, y, vida, angulo, arma);
}

ObjetoJuego *Modelo::crearObjeto(Type tipo) {
    if (tipo == Type::comida) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 5, 1, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::kitsMedicos) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 5, 2, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::llave) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 4, 2, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::balas) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 5, 3, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::sangre) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 8, 0, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::cruz) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 1, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::copa) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::cofre) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::corona) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::ametralladora) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 6, 4, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::lanzaCohetes) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 0, SPRITES_OBJETOS_LARGO / FRAMESY,
                      SPRITES_OBJETOS_ANCHO / FRAMESX);
        return new ObjetoJuego(std::move(sprite));
    } else {
        throw std::runtime_error("Tipo de objeto invalido");
    }
}
