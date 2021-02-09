#include "../include/modelo.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <thread>
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

Player &Modelo::getPlayer() {
    return *(this->jugador);
}

Map &Modelo::obtenerMapa() {
    return this->mapa;
}

Modelo::Modelo(Ventana &ventana, int idJugador, ProtectedQueue<Actualizacion *> &updates) :
        ventana(ventana),
        idJugador(idJugador),
        jugador(),
        enemigos(),
        entidades(),
        anunciador(ventana),
        partidaTerminada(false),
        updates(updates) {
    this->jugador = new Player("../../client/resources/images/Weapons.png", this->ventana.obtener_render(),
                               this->idJugador);

}

Modelo::~Modelo() {
/*  delete this->jugador;
  for (std::map<int,Enemigo*>::iterator it=enemigos.begin(); it!=enemigos.end(); ++it){
        delete it->second;
  }
  for (std::map<int,ObjetoJuego*>::iterator it=entidades.begin(); it!=entidades.end(); ++it){
        delete it->second;
  }*/
}

bool Modelo::inicializar() {
/*  std::chrono::milliseconds duration(100);
  std::this_thread::sleep_for(duration);
  bool actualice = false;
  while (! actualice){*/
    return procesarActualizaciones();
/*     std::chrono::milliseconds duration(100);
     std::this_thread::sleep_for(duration);
     std::cout << "actualice por primera vez\n";
  }
*/
}

std::vector<double> &Modelo::getZBuffer() {
    return this->zbuffer;
}

void normalizarAnguloEnRango(double &angulo, bool &esVisible) {//cheq esa referencia
    if (angulo < -PI) {
        angulo += 2 * PI;
    } else if (angulo > PI) {
        angulo -= 2 * PI;
    }
    double absAngulo = abs(angulo);
    if (absAngulo < PI / 6) {
        esVisible = true;
    }
}

void Modelo::renderizarObjeto(ObjetoDibujable *objeto, int &alturaSprite, int &x, int &y, double &distanciaObjeto) {
//  int anchuraColumna = alturaSprite / SPRITE_LARGO;
    int tamanioBuffer = zbuffer.size();
    int anchoSprite = objeto->obtenerAnchura();
    for (int i = 0; i < anchoSprite; i++) {
        int posBuffer = x + i;
        if (this->zbuffer[tamanioBuffer - 1 - posBuffer] > distanciaObjeto) {
            SDL_Rect dimension, dest;
            dimension.x = i;//suma offset
            dimension.y = 0;//sumaoffset
            dimension.w = 1;
            dimension.h = alturaSprite;
            dest.x = posBuffer;
            dest.y = y - 40;
            dest.w = 1;
            dest.h = y + alturaSprite;
            objeto->renderizarColumna(dimension, dest);
        }
    }
}

bool compararDistanciasObjetos(ObjetoDibujable *objeto1, ObjetoDibujable *objeto2) {
    return (objeto1->getDistanciaParcialAJugador() < objeto2->getDistanciaParcialAJugador());
}

bool Modelo::verificarVisibilidadDeObjeto(Posicion &posObjeto) {
    bool esVisible;
    Posicion &posJugador = jugador->getPosicion();
    double dy = (posObjeto.pixelesEnY() - posJugador.pixelesEnY());
    double dx = (posObjeto.pixelesEnX() - posJugador.pixelesEnX());
    double anguloItem = atan(dy / dx);
    normalizarAnguloEnRango(anguloItem, esVisible);
    return esVisible;
}

void Modelo::verificarItemsEnRango(std::vector<ObjetoDibujable *> &objetosVisibles) {
    bool esVisible = false;
    std::map<int, ObjetoJuego *>::iterator itItem;
    for (itItem = this->entidades.begin(); itItem != this->entidades.end(); ++itItem) {
        Posicion &posItem = itItem->second->getPosicion();
        esVisible = verificarVisibilidadDeObjeto(posItem);
        if (esVisible) {
            objetosVisibles.push_back(itItem->second);
            double distanciaAItem = posItem.distanciaA(this->jugador->getPosicion());
            itItem->second->setDistanciaParcialAJugador(distanciaAItem);
        }
    }
}

void Modelo::verificarEnemigosEnRango(std::vector<ObjetoDibujable *> &objetosVisibles) {
    bool esVisible = false;
    std::map<int, Enemigo *>::iterator itEnemigo;
    for (itEnemigo = this->enemigos.begin(); itEnemigo != this->enemigos.end(); ++itEnemigo) {
        Posicion &posEnemigo = itEnemigo->second->getPosicion();
        esVisible = verificarVisibilidadDeObjeto(posEnemigo);
        if (esVisible) {
            objetosVisibles.push_back(itEnemigo->second);
            double distanciaAEnemigo = posEnemigo.distanciaA(this->jugador->getPosicion());
            itEnemigo->second->setDistanciaParcialAJugador(distanciaAEnemigo);
        }
    }
}

void Modelo::renderizarObjetosDibujables(std::vector<ObjetoDibujable *> &objetosVisibles) {
    int cantidadItemsVisibles = objetosVisibles.size();
    for (int i = 0; i < cantidadItemsVisibles; i++) {
        //ojo que el angulo del item NO esta normalizado
        Posicion &posObjeto = objetosVisibles[i]->getPosicion();
        Posicion &posJugador = jugador->getPosicion();
        double dy = (posObjeto.pixelesEnY() - posJugador.pixelesEnY());
        double dx = (posObjeto.pixelesEnX() - posJugador.pixelesEnX());
        double anguloObjeto = atan(dy / dx);
        double distancia = objetosVisibles[i]->getDistanciaParcialAJugador();
        int alturaSprite = floor((ALTO_CELDA / distancia) * DIST_PLANO_P);
        int y0 = floor(ALTURA_CANVAS / 2) - floor(alturaSprite / 2);//cheq el segundo floor
        int y1 = y0 + alturaSprite;
        double x0 = tan(anguloObjeto) * DIST_PLANO_P;
        int x = (ANCHO_CANVAS / 2) + x0 - (SPRITE_ANCHO / 2);
        this->renderizarObjeto(objetosVisibles[i], alturaSprite, x, y1, distancia);
    }
}

void Modelo::verificarObjetosEnRangoDeVista() {
    std::vector<ObjetoDibujable *> objetosVisibles;
    this->verificarItemsEnRango(objetosVisibles);
    this->verificarEnemigosEnRango(objetosVisibles);
    std::sort(objetosVisibles.begin(), objetosVisibles.end(), compararDistanciasObjetos);
    this->renderizarObjetosDibujables(objetosVisibles);
}

void Modelo::renderizar() {
    //  std::vector<int> ranking;
    //  ranking.push_back(1111);
    //  ranking.push_back(111);
    //  this->terminoPartida(ranking);
    if (!partidaTerminada) {
        this->jugador->renderizar();

        for (std::map<int, Enemigo *>::iterator it = enemigos.begin(); it != enemigos.end(); ++it) {
            it->second->actualizar(500, 300, 4, 0, 0, 0, false, 50);
            Enemigo *enemigo = it->second;
            //enemigo->renderizar();
        }
        verificarObjetosEnRangoDeVista();
    } else {
        this->anunciador.renderizar();
    }


}

void Modelo::actualizarJugador(int x, int y, int vida, int angulo, int idArma,
                               bool disparando, int puntaje, int cantVidas,
                               int balas) {
    this->jugador->actualizar(x, y, vida, angulo, idArma, disparando, puntaje, cantVidas, balas);
}

void Modelo::actualizarEnemigo(int id, int vida, bool disparando,
                               int posx, int posy, int idArma,
                               int anguloJugador, int angulo, int puntaje) {
    Enemigo *enemigo;
    try {
        enemigo = this->enemigos.at(id);
    } catch (std::out_of_range &e) {
        enemigo = new Enemigo(this->ventana.obtener_render(), 4);
        this->enemigos.insert({id, enemigo});
        std::cerr << "agrego un enemigo\n";
    }

    this->enemigos[id]->actualizar(posx, posy, idArma, angulo, anguloJugador,
                                   vida, disparando, puntaje);
}

void Modelo::actualizarObjeto(int id, Type tipo, int posx, int posy) {
    if (tipo.getName() != "noItem"){
      ObjetoJuego* objeto;
          try {
              objeto = this->entidades.at(id);

          } catch (std::out_of_range &e) {
              objeto = this->crearObjeto(tipo);
              this->entidades.insert({id, objeto});
              std::cerr << "creo un obejto: " << tipo.getName() << "\n";
          }
          this->entidades[id]->settear_estado(posx, posy);
    }        
}

void Modelo::terminoPartida(std::vector<int> &rankingJugadores) {

    this->anunciador.settearGanadores(rankingJugadores, jugador, enemigos);
    this->partidaTerminada = true;
}


ObjetoJuego *Modelo::crearObjeto(Type tipo) {
    if (tipo.getName() == "comida") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 1, 5, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "kitsMedicos") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 5, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "llave") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 4, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "balas") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 5, 3, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "sangre") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 8, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "cruz") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 1, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "copa") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "cofre") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "corona") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "ametralladora") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 6, 4, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "lanzaCohetes") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 7, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "barril") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 2, 7, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "agua") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 2, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "tanque") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 3, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "mesa") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 4, 0, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "lampara") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 0, 1, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "muertoColgante") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 2, 1, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else if (tipo.getName() == "planta") {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 0, 2, SPRITES_OBJETOS_LARGO,
                      SPRITES_OBJETOS_ANCHO);
        return new ObjetoJuego(std::move(sprite));
    } else {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 0, 0, 0,
                      0);
        return new ObjetoJuego(std::move(sprite));
    }
}

void Modelo::actualizar() {
    this->zbuffer.clear();
}

bool Modelo::procesarActualizaciones() {
//
    try {
        Actualizacion *actualizacion = this->updates.obtener_dato();
        std::cout << "proceso\n";
        EstadoJuego &estadoJuego = actualizacion->obtenerEstadoJuego();
        std::map<int, Jugador *> &jugadores = estadoJuego.obtenerJugadores();
        std::map<int, Jugador *>::iterator it;
        Jugador *jugador = jugadores.at(this->idJugador);

        int vida = jugador->puntos_de_vida();
        int posx = jugador->getPosicion().pixelesEnX();
        int posy = jugador->getPosicion().pixelesEnY();
        int angulo = jugador->getAnguloDeVista();
        int idArma = jugador->getArma()->getId();
        int puntaje = jugador->obtenerPuntosTotales();
        bool disparando = jugador->estaDisparando();
        int cantVidas = jugador->cant_de_vida();
        int balas = jugador->cantidad_balas();
        this->actualizarJugador(posx, posy, vida, angulo, idArma,
                                disparando, puntaje, cantVidas, balas);
        for (it = jugadores.begin(); it != jugadores.end(); it++) {
            if (it->second->getId() != idJugador) {
                int idE = it->first;
                int vidaE = it->second->puntos_de_vida();
                int posxE = it->second->getPosicion().pixelesEnX();
                int posyE = it->second->getPosicion().pixelesEnY();
                int idArmaE = idArma;
                int anguloJugador = angulo;
                int anguloE = it->second->getAnguloDeVista();
                bool disparandoE = it->second->estaDisparando();
                int puntajeE = it->second->obtenerPuntosTotales();
                this->actualizarEnemigo(idE, vidaE, disparandoE, posxE,
                                        posyE, idArmaE, anguloJugador,
                                        anguloE, puntajeE);
            }
        }
        std::cerr << "cargo mapa" << std::endl;
        this->mapa = estadoJuego.obtenerMapa();
        std::vector<Item *> items = this->mapa.obtenerItems();
        for (int i = 0; i < items.size(); i++) {
            Item *item = items[i];
            int idI = item->getId();
            Type tipo = item->getTipo();
            int posxI = item->obtenerPosicion().pixelesEnX();
            int posyI = item->obtenerPosicion().pixelesEnY();
            this->actualizarObjeto(idI, tipo, posxI, posyI);
        }
        if (actualizacion->terminoPartida()) {
            std::vector<int> ordenRanking = actualizacion->obtenerRanking();
            this->terminoPartida(ordenRanking);
        }
        delete actualizacion;
        std::cout << "me llega \n";

        return true;
    } catch(QueueException &qe){
        std::cerr << "no hay actualizacion\n";
    }catch (std::exception &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "falla en actualizacion" << std::endl;

        return false;

    }


}
