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
    ObjetoJuego* comida = crearObjeto(Type::comida);
    this->entidades.insert(std::make_pair(1,comida));
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

void Modelo::renderizarSprite(ObjetoJuego* objeto,int& anchoTexturaFoto,int& anchuraColumna,int& x,int& y1,int& alturaTexturaDibujo,int& distanciaObjeto){
int tamanioBuffer = zbuffer.size();
  for (int i = 0; i < anchoTexturaFoto; i++){
    for (int j = 0; j < anchuraColumna; j++){
      int posBuffer = x + (i - 1) * anchuraColumna + j;
      if (this->zbuffer[tamanioBuffer - 1 -posBuffer] > distanciaObjeto){
        SDL_Rect dimension,dest;

      dimension.x = i;//suma offset
      dimension.y = 0;//sumaoffset
      dimension.w = 1;
      dimension.h = alturaTexturaDibujo;

      dest.x = posBuffer;
      dest.y = y1;
      dest.w = 1;
      dest.h = alturaTexturaDibujo + y1;

      objeto->renderizarColumna(dimension,dest);
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
  double distanciaPlanoProyeccion = (800 / 2) / tan(pi/6.0);//sale de raycasting// el 800 es el ancho canvas
  for (it = this->entidades.begin(); it != this->entidades.end(); ++it){
    Posicion& posItem = it->second->getPosicion();
    int dy = posItem.pixelesEnY() - jugador->getPosicion().pixelesEnY();
    int dx = posItem.pixelesEnX() - jugador->getPosicion().pixelesEnX();
    double anguloItem = atan(dy/dx);
    double diferenciaAngulo = anguloJugador - anguloItem;
    normalizarAnguloEnRango(diferenciaAngulo,esVisible);
    int distanciaAItem = posItem.distanciaA(this->jugador->getPosicion());
    if (esVisible){
      it->second->setDistanciaParcialAJugador(distanciaAItem);
      itemsVisibles.push_back(it->second);
    }
  }
   std::sort(itemsVisibles.begin(), itemsVisibles.end(),compararDistanciasSprites);

  int cantidadItemsVisibles = itemsVisibles.size();
  for (int i = 0;i < cantidadItemsVisibles; i++){
    Posicion& posItem = it->second->getPosicion();//refactorizar
    double anguloItem = atan(posItem.pixelesEnY()/posItem.pixelesEnX());//refactorizar
    int distancia = itemsVisibles[i]->getDistanciaParcialAJugador();
      double alturaSprite = altoCelda / distanciaPlanoProyeccion * distancia;
      int y0 = (800 / 2) - alturaSprite / 2;// el 800 es el ancho canvas
      int y1 = y0 + alturaSprite;
      int alturaTexturaDibujo = y1 - y0;
      int anchoTexturaDibujo = alturaTexturaDibujo;
      int anchoTexturaFoto = 64;//a qchequeer3
      int alturaTexturaFoto = 64;//a chequear
      int x0 = tan(anguloItem) * altoCelda;
      int x = (800 / 2) + x0 - (anchoTexturaFoto / 2);// el 800 es el ancho canvas
      int anchuraColumna = alturaTexturaDibujo / alturaTexturaFoto;
      this->renderizarSprite(itemsVisibles[i],anchoTexturaFoto,anchuraColumna,x,y1,alturaTexturaDibujo,distancia);
  }
}

void Modelo::verificarEnemigosEnRango(){

}

void Modelo::verificarObjetosEnRangoDeVista(){
  this->verificarItemsEnRango();
  this->verificarEnemigosEnRango();
}


void Modelo::renderizar() {
    this->jugador->actualizar(318, 420, 100, 0, 4, false, 50, 3, 5);
    this->jugador->renderizar();
  //  this->verificarObjetosEnRangoDeVista();
    //this->verificarObjetosEnRangoDeVista();
    // verificar items si estan en posicion;
    // verificar enemigos si estan en posicion correcta;

    for (std::map<int,Enemigo*>::iterator it=enemigos.begin(); it!=enemigos.end(); ++it){
          it->second->actualizar(500, 300, 4, 0, 0, 100, true);
          it->second->renderizar();
    }
    ObjetoJuego* objeto = entidades.at(static_cast<int>(Type::comida));//cambiar lo de las keys
    objeto->settear_estado(400, 420);
    verificarObjetosEnRangoDeVista();
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

void Modelo::actualizarObjeto(int id,Type tipo, int posx, int posy) {

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
