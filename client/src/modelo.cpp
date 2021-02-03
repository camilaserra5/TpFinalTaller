#include "../include/modelo.h"
#include <iostream>
#include <math.h>
#include <algorithm>
//#include "rayo.h"

#define SPRITES_OBJETOS_ANCHO  65
#define SPRITES_OBJETOS_LARGO 73
#define SPRITE_OBJETOS "../../client/resources/images/Objects.png"
#define FRAMESX 5
#define FRAMESY 10

Player& Modelo::getPlayer(){
  return *(this->jugador);
}

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
        comida->settear_estado(325, 420);
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

void Modelo::renderizarSprite(ObjetoJuego* objeto,int& anchoTexturaFoto,int& anchuraColumna,int& x,int& y1,int& alturaTexturaDibujo,double& distanciaObjeto){

int tamanioBuffer = zbuffer.size();
std::cout << "anchuraColumna: "<< anchuraColumna << "\n";
  for (int i = 0; i < anchoTexturaFoto; i++){
    for (int j = 0; j < anchuraColumna; j++){
      int posBuffer = x + (i - 1) * anchuraColumna + j;

      if (this->zbuffer[tamanioBuffer - 1 -posBuffer] > distanciaObjeto){
        SDL_Rect dimension,dest;

      dimension.x = i;//suma offset
      dimension.y = 0;//sumaoffset
      dimension.w = 1;
      dimension.h = 64 - 1;

      dest.x = tamanioBuffer - 1 -posBuffer;
      dest.y = y1;
      dest.w = 1;
      dest.h = 63;

      objeto->renderizarColumna(dimension,dest);
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
  std::cout << "lla posicion del jugador en es x: " << jugador->getPosicion().pixelesEnX() << "y en Y: " << jugador->getPosicion().pixelesEnY() << "\n";

  bool esVisible = false;
  std::map<int, ObjetoJuego *>::iterator it;
  std::vector<ObjetoJuego*> itemsVisibles;
  double altoCelda = 40;//epues pasarlo
  double distanciaPlanoProyeccion = (ANCHO_CANVAS / 2) / tan(pi/6.0);//sale de raycasting// el 800 es el ancho canvas
  for (it = this->entidades.begin(); it != this->entidades.end(); ++it){
    Posicion& posItem = it->second->getPosicion();
    int dy = posItem.pixelesEnY() - jugador->getPosicion().pixelesEnY();
    int dx = posItem.pixelesEnX() - jugador->getPosicion().pixelesEnX();
    double anguloItem = atan(dy/dx);
    double diferenciaAngulo = anguloJugador - anguloItem;
    normalizarAnguloEnRango(diferenciaAngulo,esVisible);
    int distanciaAItem = posItem.distanciaA(this->jugador->getPosicion());
    if (esVisible){
      std::cout << "es visible \n";
      it->second->setDistanciaParcialAJugador(distanciaAItem);
      itemsVisibles.push_back(it->second);
    } else {
        std::cout << "no es visible \n";
    }
  }
   std::sort(itemsVisibles.begin(), itemsVisibles.end(),compararDistanciasSprites);
  int cantidadItemsVisibles = itemsVisibles.size();

  /********************************************************/
  for (int i = 0;i < cantidadItemsVisibles; i++){
    Posicion& posItem = itemsVisibles[i]->getPosicion();//refactorizar
    double pixelesY = posItem.pixelesEnY();
    double pixelesX = posItem.pixelesEnX();
    double anguloItem = atan(pixelesY/pixelesX);//refactorizar
    double distancia = itemsVisibles[i]->getDistanciaParcialAJugador();
    double alturaSprite = (altoCelda / distancia) * distanciaPlanoProyeccion;
  //  std::cout << "ang: " << anguloItem << "\n";

    int y0 = floor(ALTURA_CANVAS / 2) - alturaSprite / 2;// el 800 es el ancho canvas
    int y1 = y0 + alturaSprite;
    int alturaTexturaDibujo = alturaSprite;
    int anchoTexturaDibujo = alturaTexturaDibujo;
    int anchoTexturaFoto = SPRITES_OBJETOS_ANCHO;//a qchequeer3
    int alturaTexturaFoto = SPRITES_OBJETOS_LARGO;//a chequear
    double x0 = tan(anguloItem) * distanciaPlanoProyeccion;
    int x = (ANCHO_CANVAS / 2) + x0 - (anchoTexturaDibujo / 2);
    std::cout << "distanciaP: " << distanciaPlanoProyeccion << "a: " << anchoTexturaDibujo << "\n";

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
    // verificar items si estan en posicion;
    // verificar enemigos si estan en posicion correcta;

    for (std::map<int,Enemigo*>::iterator it=enemigos.begin(); it!=enemigos.end(); ++it){
          it->second->actualizar(500, 300, 4, 0, 0, 100, true);
          it->second->renderizar();
    }

    ObjetoJuego* objeto = entidades.at(1);//cambiar lo de las keys
    objeto->settear_estado(500, 420);
    verificarObjetosEnRangoDeVista();
    //sprite.reescalar(2,2);
  //  sprite.renderizar(250, 400, 0, NULL);

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
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 0, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::kitsMedicos) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 5, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::llave) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 4, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::balas) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 5, 3, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::sangre) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 8, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::cruz) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 1, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::copa) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::cofre) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::corona) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::ametralladora) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 6, 4, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::lanzaCohetes) {
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 7, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if(tipo == Type::barril){
      Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 2, 7, SPRITES_OBJETOS_LARGO,
                    SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::agua){
      Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 2, 0, SPRITES_OBJETOS_LARGO,
                    SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::tanque){
      Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 3, 0, SPRITES_OBJETOS_LARGO,
                    SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::mesa){
      Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 4, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::lampara){
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 0, 1, SPRITES_OBJETOS_LARGO,
                        SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::muertoColgante){
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 2, 1, SPRITES_OBJETOS_LARGO,
                        SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo == Type::planta){
        Sprite sprite(ventana->obtener_render(), SPRITE_OBJETOS, 0, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
          return new ObjetoJuego(std::move(sprite));
    } else {
        throw std::runtime_error("Tipo de objeto invalido");
    }
}
