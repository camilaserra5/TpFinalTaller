#include "../include/modelo.h"
#include <iostream>
#include <math.h>
#include <algorithm>
//#include "rayo.h"

#define SPRITES_OBJETOS_ANCHO 320
#define SPRITES_OBJETOS_LARGO 650
#define SPRITE_OBJETOS "../../client/resourses/images/Objects.png"
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
    Enemigo* enemigo = new Enemigo(this->ventana->obtener_render(), 4);
    this->enemigos.insert(std::make_pair(111,enemigo));

}

std::vector<double>& Modelo::getZBuffer(){
  return this->zbuffer;
}


void normalizarAnguloEnRango(double& diferenciaAngulo,bool& esVisible){
  double pi = 2 * acos(0.0);
  if (diferenciaAngulo < -pi){
    diferenciaAngulo += 2 * pi;
  } else if (diferenciaAngulo > pi){
    diferenciaAngulo -= 2 * pi;
  }
  diferenciaAngulo = abs(diferenciaAngulo);
  if (diferenciaAngulo < pi / 6){
    esVisible = true;
  }
}

void Modelo::renderizarSprite(int& anchoTexturaFoto,int& anchuraColumna,int& x,int& y1,int& alturaTexturaFoto,int& distanciaObjeto){
  for (int i = 0; i < anchoTexturaFoto; i++){
    for (int j = 0; j < anchuraColumna; j++){
      int posBuffer = x + (i - 1) * anchuraColumna + j;
      if (this->zbuffer[posBuffer] > distanciaObjeto){
        //toda la bola de sdl de dibujar una columna (como las paredes de raycasting)
      }
    }
  }
}

bool compararDistanciasSprites(ObjetoJuego* objeto1,ObjetoJuego* objeto2){
  return (objeto1->getDistanciaParcialAJugador() < objeto2->getDistanciaParcialAJugador());
}

void Modelo::verificarItemsEnRango(){
  double pi = 2 * acos(0.0);
  double anguloJugador = jugador->getAnguloDeVista();
  bool esVisible = false;
  std::map<int, ObjetoJuego *>::iterator it;
  std::vector<ObjetoJuego*> itemsVisibles;
  int altoCelda = 40;//epues pasarlo
  double distanciaPlanoProyeccion = (800 / 2) / tan(pi/6.0);//sale de raycasting
  for (it = this->entidades.begin(); it != this->entidades.end(); ++it){
    Posicion& posItem = it->second->getPosicion();
    double anguloItem = atan(posItem.pixelesEnY()/posItem.pixelesEnX());
    double diferenciaAngulo = anguloJugador - anguloItem;
    normalizarAnguloEnRango(diferenciaAngulo,esVisible);
    double distanciaAItem = posItem.distanciaA(this->jugador->getPosicion());
    double alturaSprite = altoCelda / distanciaPlanoProyeccion * distanciaAItem;
    if (esVisible){
      it->second.setDistanciaParcialAJugador(distanciaAItem);
      itemsVisibles.push_back(it->second);
    }
  }
   std::sort(this->itemsVisibles.begin(), this->itemsVisibles.end(),compararDistanciasSprites);

  int cantidadItemsVisibles = itemsVisibles.size();
  for (int i = 0;i < cantidadItemsVisibles; i++){


      int y0 = (ANCHO_CANVAS / 2) - alturaSprite / 2;
      int y1 = y0 + alturaSprite;
      int alturaTexturaDibujo = y1 - y0;
      int anchoTexturaDibujo = alturaTextura;
      int anchoTexturaFoto = 64;//a qchequeer3
      int alturaTexturaFoto = 64;//a chequear
      int x0 = tan(anguloItem) * altoCelda;
      int x = (ANCHO_CANVAS / 2) + x0 - (anchoTexturaFoto / 2);
      int anchuraColumna = alturaTexturaDibujo / alturaTexturaFoto;
      this->renderizarSprite(anchoTexturaFoto,anchuraColumna,x,y1,alturaTexturaFoto,distanciaAItem);
  }
}

void Modelo::verificarEnemigosEnRango(){

}

void Modelo::verificarObjetosEnRangoDeVista(){
  this->verificarItemsEnRango();
  this->verificarEnemigosEnRango();
}


void Modelo::renderizar() {
  int posx(318),posy(420),vida(100),angulo(50),idArma(4);
    this->jugador->actualizar(318, 420, 100, 50, 4, false, 50, 3, 5);
    this->jugador->renderizar();

    //this->verificarObjetosEnRangoDeVista();
    // verificar items si estan en posicion;
    // verificar enemigos si estan en posicion correcta;

    for (std::map<int,Enemigo*>::iterator it=enemigos.begin(); it!=enemigos.end(); ++it){
      int posx(500), posy(300),idArma(4),anguloEnemigo(0),anguloJugador(90),vida(100);
          it->second->actualizar(500, 300, 4, 0, 90, 100, true);
          it->second->renderizar();
    }
}

void Modelo::actualizarJugador(int x, int y, int vida, int angulo, int idArma,
                        bool disparando, int puntaje, int cantVidas,
                        int balas){
    this->jugador->actualizar(x, y, vida, angulo, idArma, disparando, puntaje, cantVidas, balas);
}

void Modelo::actualizarEnemigo(int id, int vida, bool disparando,
                        int posx, int posy, int idArma,
                        int anguloJugador, int angulo){

    if (this->enemigos[id] == NULL){
          Enemigo* enemigo = new Enemigo(this->ventana->obtener_render(), 4);
    }
    this->enemigos[id]->actualizar(posx, posy, idArma, angulo, anguloJugador, vida, disparando);
}

void Modelo::actualizarObjeto(int id,Type tipo int posx, int posy) {

    if (entidades[id] == NULL) {
        ObjetoJuego *objeto = this->crearObjeto(tipo);
        this->entidades[id] = objeto;
    }
    this->entidades[id]->settear_estado(posx, posy);

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
