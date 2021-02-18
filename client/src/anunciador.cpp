#include "../include/anunciador.h"
#include <config.h>

#define FONT FONTS_DIR NOUGAT_FONT

Anunciador::Anunciador(Ventana &ventana) : ventana(ventana), mostrar(false) {}

Anunciador::~Anunciador() {}

void Anunciador::settearInformacion(Player *jugador, std::map<int, Enemigo *> &enemigos) {
    this->jugador = jugador;
    this->enemigos = enemigos;
}

void Anunciador::settearGanadores(std::vector<int> &ganadores) {
    Fonts fuentes;
    int x = 200;
    int y = 300;
    fuentes.addFont("ganadores", FONT, 65);//rutGanadores
    fuentes.addFont("jugador", FONT, 35);//rutaFontJUgadores
    SDL_Color color{255, 0, 0};
    Label ganador(100, 100, "GANADORES", fuentes.getFont("ganadores"), color, ventana.obtener_render());
    this->ganadores.push_back(ganador);
    int cantGanadores = ganadores.size();
    for (int i = 0; i < cantGanadores; i++) {
        int id = ganadores[i];
        if (jugador->getId() == id) {
            int logro = jugador->getPuntaje();
            std::string infoJugador = std::to_string(id);
            std::string puntaje = std::to_string(logro);
            std::string informacion = infoJugador + "  " + puntaje;
            Label label(x, y, informacion, fuentes.getFont("jugador"), color, ventana.obtener_render());
            this->ganadores.push_back(label);
            y += 100;
        } else {
            Enemigo *enemigo = enemigos.find(ganadores[i])->second;
            int logro = enemigo->getPuntaje();
            std::string infoJugador = std::to_string(id);
            std::string puntaje = std::to_string(logro);
            std::string informacion = infoJugador + "  " + puntaje;
            Label label(x, y, informacion, fuentes.getFont("jugador"), color, ventana.obtener_render());
            this->ganadores.push_back(label);
            y += 100;
        }
    }
    this->mostrar = true;
}

void Anunciador::renderizar() {
    if (this->mostrar) {
        for (Label &ganador: this->ganadores) {
            ganador.setLabelText();
            ganador.draw();
        }
    }
}
