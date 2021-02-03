#include "../include/modelo.h"
#include <iostream>
#include <math.h>
#include <algorithm>
//#include "rayo.h"
#define SPRITE_LARGO 63
#define SPRITE_ANCHO SPRITE_LARGO
#define SPRITES_OBJETOS_ANCHO  64
#define SPRITES_OBJETOS_LARGO 73
#define SPRITE_OBJETOS "../../client/resources/images/Objects.png"
#define FRAMESX 5
#define FRAMESY 10
#define ALTO_CELDA 40 //cambiar
#define DIST_PLANO_P 692.820323//(ANCHO_CANVAS / 2) / tan(pi/6.0)
#define PI 3.141592653

Player& Modelo::getPlayer(){
  return *(this->jugador);
}

Modelo::Modelo(Ventana& ventana, int idJugador) :
        ventana(ventana),
        idJugador(idJugador),
        jugador(),
        enemigos(),
        entidades(),
        anunciador(ventana),
        partidaTerminada(false){}

Modelo::~Modelo() {}

void Modelo::inicializar() {
    this->jugador = new Player("../../client/resources/images/Weapons.png", this->ventana.obtener_render(),
                                this->idJugador);
    Enemigo* enemigo = new Enemigo(this->ventana.obtener_render(), 4);
    this->enemigos.insert(std::make_pair(111,enemigo));
    ObjetoJuego* comida = crearObjeto(Type::comida);
        comida->settear_estado(325, 420);
    this->entidades.insert(std::make_pair(1,comida));
}

std::vector<double>& Modelo::getZBuffer(){
  return this->zbuffer;
}

void normalizarAnguloEnRango(double& angulo,bool& esVisible){//cheq esa referencia
  if (angulo < -PI){
    angulo += 2 * PI;
  } else if (angulo > PI){
    angulo -= 2 * PI;
  }
  double absAngulo = abs(angulo);
  if (absAngulo < PI / 6){
    esVisible = true;
  }
}

void Modelo::renderizarObjeto(ObjetoDibujable* objeto,int& alturaSprite,int& x,int& y,double& distanciaObjeto){
//  int anchuraColumna = alturaSprite / SPRITE_LARGO;
  int tamanioBuffer = zbuffer.size();
  for (int i = 2; i < SPRITE_ANCHO; i++){
    int posBuffer = x + i;
    if (this->zbuffer[tamanioBuffer - 1 -posBuffer] > distanciaObjeto){
      SDL_Rect dimension,dest;
      dimension.x = i;//suma offset
      dimension.y = 0;//sumaoffset
      dimension.w = 1;
      dimension.h = alturaSprite;
      dest.x = posBuffer;
      dest.y = y - 20;
      dest.w = 1;
      dest.h = y + alturaSprite - 20;
      objeto->renderizarColumna(dimension,dest);
    }
  }
}

bool compararDistanciasObjetos(ObjetoDibujable* objeto1,ObjetoDibujable* objeto2){
  return (objeto1->getDistanciaParcialAJugador() < objeto2->getDistanciaParcialAJugador());
}

bool Modelo::verificarVisibilidadDeObjeto(Posicion& posObjeto){
  bool esVisible;
  Posicion& posJugador = jugador->getPosicion();
  double dy = (posObjeto.pixelesEnY() - posJugador.pixelesEnY());
  double dx = (posObjeto.pixelesEnX() - posJugador.pixelesEnX());
  double anguloItem = atan(dy/dx);
  normalizarAnguloEnRango(anguloItem,esVisible);
  return esVisible;
}

void Modelo::verificarItemsEnRango(std::vector<ObjetoDibujable*>& objetosVisibles){
  bool esVisible = false;
  std::map<int, ObjetoJuego *>::iterator itItem;
//  double DIST_PLANO_P = (ANCHO_CANVAS / 2) / tan(PI/6.0);
  for (itItem = this->entidades.begin(); itItem != this->entidades.end(); ++itItem){
    Posicion& posItem = itItem->second->getPosicion();
      esVisible = verificarVisibilidadDeObjeto(posItem);
      if (esVisible){
        objetosVisibles.push_back(itItem->second);
        double distanciaAItem = posItem.distanciaA(this->jugador->getPosicion());
        itItem->second->setDistanciaParcialAJugador(distanciaAItem);
      }
  }
}

void Modelo::verificarEnemigosEnRango(std::vector<ObjetoDibujable*>& objetosVisibles){
  bool esVisible = false;
  std::map<int,Enemigo*>::iterator itEnemigo;
  for (itEnemigo = this->enemigos.begin(); itEnemigo != this->enemigos.end(); ++itEnemigo){
      Posicion& posEnemigo = itEnemigo->second->getPosicion();
      esVisible = verificarVisibilidadDeObjeto(posEnemigo);
      if (esVisible){
        objetosVisibles.push_back(itEnemigo->second);
        double distanciaAEnemigo = posEnemigo.distanciaA(this->jugador->getPosicion());
        itEnemigo->second->setDistanciaParcialAJugador(distanciaAEnemigo);
      }
  }
}

void Modelo::renderizarObjetosDibujables(std::vector<ObjetoDibujable*>& objetosVisibles){
  int cantidadItemsVisibles = objetosVisibles.size();
  for (int i = 0;i < cantidadItemsVisibles; i++){
    //ojo que el angulo del item NO esta normalizado
    Posicion& posObjeto = objetosVisibles[i]->getPosicion();
    Posicion& posJugador = jugador->getPosicion();
    double dy = (posObjeto.pixelesEnY() - posJugador.pixelesEnY());
    double dx = (posObjeto.pixelesEnX() - posJugador.pixelesEnX());
    double anguloObjeto = atan(dy/dx);
    double distancia = objetosVisibles[i]->getDistanciaParcialAJugador();
    int alturaSprite = floor((ALTO_CELDA/distancia) * DIST_PLANO_P);
    int y0 = floor(ALTURA_CANVAS / 2) - floor(alturaSprite / 2);//cheq el segundo floor
    int y1 = y0 + alturaSprite;
    double x0 = tan(anguloObjeto) * DIST_PLANO_P;
    int x = (ANCHO_CANVAS / 2) + x0 - (SPRITE_ANCHO / 2);
    this->renderizarObjeto(objetosVisibles[i],alturaSprite,x,y1,distancia);
  }
}

void Modelo::verificarObjetosEnRangoDeVista(){
  std::vector<ObjetoDibujable*> objetosVisibles;
  this->verificarItemsEnRango(objetosVisibles);
  this->verificarEnemigosEnRango(objetosVisibles);
  std::sort(objetosVisibles.begin(), objetosVisibles.end(),compararDistanciasObjetos);
  this->renderizarObjetosDibujables(objetosVisibles);
}


void Modelo::renderizar() {
  //  std::vector<int> ranking;
  //  ranking.push_back(1111);
  //  ranking.push_back(111);
  //  this->terminoPartida(ranking);
  if (!partidaTerminada){
        this->jugador->renderizar();
        // verificar items si estan en posicion;
        // verificar enemigos si estan en posicion correcta;

        for (std::map<int,Enemigo*>::iterator it=enemigos.begin(); it!=enemigos.end(); ++it){
              it->second->actualizar(500, 300, 4, 0, 0, 0, false, 50);
              Enemigo* enemigo = it->second;
              enemigo->renderizar();
        }

        ObjetoJuego* objeto = entidades.at(1);//cambiar lo de las keys
        objeto->settear_estado(500, 420);
      //  verificarObjetosEnRangoDeVista();
        //sprite.reescalar(2,2);
      //  sprite.renderizar(250, 400, 0, NULL);
      this->jugador->actualizar(318, 420, 100, 0, 4, true, 50, 3, 5);
  }
  this->anunciador.renderizar();


}

void Modelo::actualizarJugador(int x, int y, int vida, int angulo, int idArma,
                        bool disparando, int puntaje, int cantVidas,
                        int balas){
    this->jugador->actualizar(x, y, vida, angulo, idArma, disparando, puntaje, cantVidas, balas);
}

void Modelo::actualizarEnemigo(int id, int vida, bool disparando,
                        int posx, int posy, int idArma,
                        int anguloJugador, int angulo, int puntaje){

    if (this->enemigos[id] == NULL){
          Enemigo* enemigo = new Enemigo(this->ventana->obtener_render(), 4);
    }
    this->enemigos[id]->actualizar(posx, posy, idArma, angulo, anguloJugador,
                                    vida, disparando, puntaje);
}

void Modelo::actualizarObjeto(int id,Type tipo, int posx, int posy) {

    if (entidades[id] == NULL) {
        ObjetoJuego *objeto = this->crearObjeto(tipo);
        this->entidades[id] = objeto;
    }
    this->entidades[id]->settear_estado(posx, posy);

}

void Modelo::terminoPartida(std::vector<int>& rankingJugadores){
    this->anunciador.settearInformacion(jugador, enemigos);
    this->anunciador.settearGanadores(rankingJugadores);
    this->partidaTerminada = true;
}


ObjetoJuego *Modelo::crearObjeto(Type tipo) {
    if (tipo == Type::comida) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 1, 5, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::kitsMedicos) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 5, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::llave) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 4, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::balas) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 5, 3, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::sangre) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 8, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::cruz) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 1, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::copa) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::cofre) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::corona) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::ametralladora) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 6, 4, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::lanzaCohetes) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if(tipo == Type::barril){
      Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 2, 7, SPRITES_OBJETOS_LARGO,
                    SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::agua){
      Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 2, 0, SPRITES_OBJETOS_LARGO,
                    SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::tanque){
      Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 3, 0, SPRITES_OBJETOS_LARGO,
                    SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::mesa){
      Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 4, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::lampara){
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 0, 1, SPRITES_OBJETOS_LARGO,
                        SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::muertoColgante){
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 2, 1, SPRITES_OBJETOS_LARGO,
                        SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::planta){
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 0, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
          return new ObjetoJuego(std::move(sprite));
    } else {
        throw std::runtime_error("Tipo de objeto invalido");
    }
}

void Modelo::actualizar(){
  this->zbuffer.clear();
}
