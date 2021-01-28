#include "../include/modelo.h"

#define SPRITES_OBJETOS_ANCHO 320
#define SPRITES_OBJETOS_LARGO 650
#define SPRITE_OBJETOS "../../client/resourses/images/Objects.png,"
#define FRAMESX 5
#define FRAMESY 10

Modelo::Modelo(Ventana *ventana, int idJugador) :
        ventana(ventana),
        idJugador(idJugador),
        jugadores(),
        entidades() {}

Modelo::~Modelo() {}

void Modelo::inicializar() {
    Player *player = new Player("../../client/resources/images/Weapons.png", this->ventana->obtener_render(),
                                this->idJugador);
    this->jugadores.insert(std::make_pair(this->idJugador, player));
}

void Modelo::renderizar() {
    this->jugadores[this->idJugador]->settear_estado(318, 420, 100, 50, 4);
    this->jugadores[this->idJugador]->renderizar();
}

void Modelo::actualizarObjeto(int id, Type tipo, int posx, int posy) {

    if (entidades[id] == NULL) {
        ObjetoJuego *objeto = this->crearObjeto(tipo);
        this->entidades[id] = objeto;
    }
    this->entidades[id]->settear_estado(posx, posy);

}

void Modelo::actualizarJugador(int x, int y, int vida, int angulo, int id, int arma) {
    this->jugadores[id]->settear_estado(x, y, vida, angulo, arma);
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
