#include "../include/modelo.h"
#include <algorithm>
#include <thread>
#include <actualizaciones/actualizacionTerminoPartida.h>
#include <actualizaciones/actualizacionInicioPartida.h>
#include <actualizaciones/actualizacionMovimiento.h>
#include <actualizaciones/actualizacionAtaque.h>
#include <actualizaciones/actualizacionCambioArma.h>
#include <actualizaciones/actualizacionAgarroItem.h>
#include <actualizaciones/actualizacionAgregarItem.h>
#include <config.h>
//#include "rayo.h"
#define SPRITE_LARGO 63
#define SPRITE_ANCHO SPRITE_LARGO
#define SPRITES_OBJETOS_ANCHO  64.8
#define SPRITES_OBJETOS_LARGO 65
#define SPRITE_OBJETOS IMGS_DIR OBJECTS_IMG
#define FRAMESX 5
#define FRAMESY 10
#define DIST_PLANO_P 692.820323//(ANCHO_CANVAS / 2) / tan(pi/6.0)
#define PI 3.141592653
#define WEAPON IMGS_DIR WEAPONS_IMG

Player &Modelo::getPlayer() {
    return *(this->jugador);
}

Map &Modelo::obtenerMapa() {
    return this->mapa;
}

Modelo::Modelo(Ventana &ventana, int idJugador, ProtectedQueue<Actualizacion *> &updates) :
        ventana(ventana),
        idJugador(idJugador),
        entidades(),
        enemigos(),
        anunciador(),
        partidaTerminada(false),
        updates(updates) {
    this->jugador = new Player(WEAPON, this->ventana.obtener_render(), this->idJugador);
}

Modelo::~Modelo() {
    delete this->jugador;
    for (auto it = enemigos.begin(); it != enemigos.end(); ++it) {
        delete it->second;
    }
    for (auto it = entidades.begin(); it != entidades.end(); ++it) {
        delete it->second;
    }
}

void Modelo::setMapa(Map &&mapa) {
    this->mapa = std::move(mapa);
}

bool Modelo::inicializar() {
    return procesarActualizaciones();
}

std::vector<double> &Modelo::getZBuffer() {
    return this->zbuffer;
}

bool normalizarAnguloEnRango(double &angulo) {
    if (angulo < -PI) {
        angulo += 2.0 * PI;
    } else if (angulo > PI) {
        angulo -= 2.0 * PI;
    }
    double absAngulo = abs(angulo);
    if (absAngulo < PI / 6.0) {
        return true;
    }
    return false;
}

void
Modelo::renderizarObjeto(ObjetoDibujable *objeto, int &alturaSprite,
                         int &x, int &drawStart, double &distanciaObjeto) {
    int anchoSprite = objeto->obtenerAnchura();
    //float drawEnd;
    for (int i = 0; i < anchoSprite; i++) {
        int posBuffer = x + i;
        if (this->zbuffer[posBuffer] > distanciaObjeto) {
            if (alturaSprite >= ALTURA_CANVAS) {
                drawStart = 100;
            } else {
                drawStart = 500 - alturaSprite;
            }
            SDL_Rect dimension, dest;
            dimension.x = i;//suma offset
            dimension.y = 0;//sumaoffset
            dimension.w = 1;
            dimension.h = 0;
            dest.x = posBuffer;
            dest.y = drawStart;
            dest.w = 1;
            dest.h = alturaSprite;
            objeto->renderizarColumna(dimension, dest);
        }
    }
}

bool compararDistanciasObjetos(ObjetoDibujable *objeto1, ObjetoDibujable *objeto2) {
    return (objeto1->getDistanciaParcialAJugador() < objeto2->getDistanciaParcialAJugador());
}

bool verificarsiEstaDelante(Posicion &posObjeto, Posicion &posJugador) {
    float angulo = posJugador.getAnguloDeVista();
    int yJugador = posJugador.pixelesEnY();
    int yObjeto = posObjeto.pixelesEnY();
    if (0 <= angulo && angulo <= PI) {
        if (yObjeto <= yJugador) return true;
        else return false;
    } else {
        if (yObjeto >= yJugador) return true;
        else return false;
    }
}

bool Modelo::verificarVisibilidadDeObjeto(Posicion &posObjeto) {
    Posicion &posJugador = jugador->getPosicion();
    float anguloDeVista = posJugador.getAnguloDeVista();
    bool estaEnSegmento = posJugador.verificarSiPerteneceAlSegmento(posObjeto);//camiar a estaEnRangoSegmento
    if (!estaEnSegmento) {
        return false;
    }
    bool enVista;
    float pendienteRecta = tan(anguloDeVista);
    float ordenadaOrigen = -posJugador.pixelesEnY() - (pendienteRecta * posJugador.pixelesEnX());
    float y = pendienteRecta * posObjeto.pixelesEnX() + ordenadaOrigen;
    if (y < 0) y = (-1) * y;
    float opuesto = abs(y - posObjeto.pixelesEnY());
    float adyacente = abs(posJugador.pixelesEnX() - posObjeto.pixelesEnX());
    if (adyacente == 0) {
        enVista = verificarsiEstaDelante(posObjeto, posJugador);
    } else {
        enVista = (abs(atan(opuesto / adyacente)) <= PI / 6);
    }
    return enVista;
}

void Modelo::verificarItemsEnRango(std::vector<ObjetoDibujable *> &objetosVisibles) {
    bool esVisible;
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
    bool esVisible;
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
        Posicion &posObjeto = objetosVisibles[i]->getPosicion();
        Posicion &posJugador = jugador->getPosicion();
        double dy = (posJugador.pixelesEnY() - posObjeto.pixelesEnY());
        double dx = (posObjeto.pixelesEnX() - posJugador.pixelesEnX());
        double difAngulo = jugador->getAnguloDeVista() - atan(dy / dx);
        double distancia = objetosVisibles[i]->getDistanciaParcialAJugador();
        if (distancia > 0) {
            int alturaSprite = floor((this->mapa.getLadoCelda() / distancia) * DIST_PLANO_P);
            int y0 = floor(ALTURA_CANVAS / 2);
            //a la altura de la pantalla le resto la altura del sprite
            //normalizarAnguloEnRango(difAngulo);
            double x0 = tan(difAngulo) * DIST_PLANO_P;
            int x = (ANCHO_CANVAS / 2) + x0 - (objetosVisibles[i]->obtenerAnchura() / 2);
            this->renderizarObjeto(objetosVisibles[i], alturaSprite, x, y0, distancia);
        }

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
    if (!partidaTerminada) {
        verificarObjetosEnRangoDeVista();
        this->jugador->renderizar();
    } else {
        this->ventana.cerrar();
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
    if (this->enemigos.count(id) == 0) {
        auto enemigo = new Enemigo(this->ventana.obtener_render(), 4);
        this->enemigos.insert({id, enemigo});
    }
    this->enemigos[id]->actualizar(posx, posy, idArma, angulo, anguloJugador,
                                   vida, disparando, puntaje);
}

void Modelo::actualizarObjeto(int id, Type tipo, int posx, int posy) {
    if (tipo.getName() != "noItem") {
        ObjetoJuego *objeto;
        try {
            this->entidades.at(id)->settear_estado(posx, posy);
        } catch (std::out_of_range &e) {
            objeto = this->crearObjeto(tipo);
            this->entidades.insert({id, objeto});
            this->entidades.at(id)->settear_estado(posx, posy);
        }
    }
}

void Modelo::terminoPartida(Ranking &rankingJugadores) {
    this->anunciador.settearGanadores(rankingJugadores);
    this->partidaTerminada = true;
}


ObjetoJuego *Modelo::crearObjeto(Type tipo) {
    std::map<std::string, std::pair<int, int>> coord;
    coord.insert(std::make_pair("comida", std::make_pair(1, 5)));
    coord.insert(std::make_pair("kitsMedicos", std::make_pair(2, 5)));
    coord.insert(std::make_pair("llave", std::make_pair(2, 4)));
    coord.insert(std::make_pair("balas", std::make_pair(3, 5)));
    coord.insert(std::make_pair("sangre", std::make_pair(0, 8)));
    coord.insert(std::make_pair("cruz", std::make_pair(1, 6)));
    coord.insert(std::make_pair("copa", std::make_pair(2, 6)));
    coord.insert(std::make_pair("cofre", std::make_pair(3, 6)));
    coord.insert(std::make_pair("corona", std::make_pair(4, 6)));
    coord.insert(std::make_pair("ametralladora", std::make_pair(4, 5)));
    coord.insert(std::make_pair("lanzaCohetes", std::make_pair(0, 6)));
    coord.insert(std::make_pair("barril", std::make_pair(2, 7)));
    coord.insert(std::make_pair("agua", std::make_pair(2, 0)));
    coord.insert(std::make_pair("tanque", std::make_pair(3, 0)));
    coord.insert(std::make_pair("mesa", std::make_pair(4, 0)));
    coord.insert(std::make_pair("lampara", std::make_pair(0, 1)));
    coord.insert(std::make_pair("muertoColgante", std::make_pair(2, 1)));
    coord.insert(std::make_pair("planta", std::make_pair(0, 2)));

    if (coord.count(tipo.getName()) == 0) {
        Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, 0, 0, 0,
                      0);
        return new ObjetoJuego(std::move(sprite));
    }
    Sprite sprite(ventana.obtener_render(), SPRITE_OBJETOS, coord.at(tipo.getName()).first,
                  coord.at(tipo.getName()).second,
                  SPRITES_OBJETOS_LARGO, SPRITES_OBJETOS_ANCHO);
    return new ObjetoJuego(std::move(sprite));
}

void Modelo::actualizar() {
    this->zbuffer.clear();
}

void Modelo::actualizarArmaJugador(int idArma) {
    this->jugador->actualizarArma(idArma, false);
}

void Modelo::actualizarArmaEnemigos(int idArma) {
    std::map<int, Enemigo *>::iterator it;
    for (it = this->enemigos.begin(); it != this->enemigos.end(); ++it) {
        it->second->actualizarArma(idArma);
    }
}

void Modelo::actualizarEstadoAtaqueJugador(int vida, int idArma, int cant_balas, int puntaje, int cant_vidas,
                                           bool atacando) {
    this->jugador->actualizarDatosJugador(vida, cant_vidas, puntaje, cant_balas);
    this->jugador->actualizarArma(idArma, atacando);
}

void Modelo::actualizarVidaEnemigo(int id, int vida, int idArma) {
    this->enemigos.at(id)->actualizarVida(vida);
    this->enemigos.at(id)->actualizarArma(idArma);
}

void Modelo::sacarItem(int &id) {
    ObjetoJuego *objeto = this->entidades.at(id);
    delete objeto;
    this->entidades.erase(id);
}

void Modelo::actualizarBeneficioJugador(int vida, int balas, int puntos, int cant_vidas) {
    this->jugador->actualizarDatosJugador(vida, cant_vidas, puntos, balas);
}

bool Modelo::procesarActualizaciones() {
    try {
        Actualizacion *actualizacion = this->updates.obtener_dato();
        ProcesadorDeActualizaciones procesador(this, actualizacion);
        procesador.ejecutar();
        delete actualizacion;
        return true;
    } catch (QueueException &qe) {
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
        return false;
    }
    return true;
}

void Modelo::actualizarPosicionJugador(int posX, int posY, float angulo) {
    this->jugador->getPosicion().actualizar_posicion(posX, posY);
    this->jugador->getPosicion().setAngulo(angulo);
}

void Modelo::actualizarPosicionEnemigo(int idE, int posX, int posY, float angulo) {
    this->enemigos.at(idE)->actualizarPosicion(posX, posY, angulo);
}
