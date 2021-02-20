#include "../include/highscoreWindow.h"
#include "../include/background.h"
#include <config.h>

#define WOLFSTEIN_TTF_ROOT FONTS_DIR JOYSTICK_FONT
#define BACKGROUND_IMAGE_ROOT IMGS_DIR BACKGROUND_HIGHSCORE_IMG
#define FONT_SIZE_TITLE 30
#define FONT_SIZE_SUBTITLE 15
#define FONT_SIZE_NAMES 12

HighscoreWindow::HighscoreWindow(Ventana &ventana) : ventana(ventana) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /*SDL_CreateWindow("Wolfstein 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, windowFlags);*/

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    if (TTF_Init() == -1) {
        printf("Failed to init TTF\n");
        exit(1);
    }

    fonts.addFont("wolfstein-title", WOLFSTEIN_TTF_ROOT, FONT_SIZE_TITLE);
    fonts.addFont("wolfstein-subtitle", WOLFSTEIN_TTF_ROOT, FONT_SIZE_SUBTITLE);
    fonts.addFont("wolfstein-names", WOLFSTEIN_TTF_ROOT, FONT_SIZE_NAMES);

    this->renderer = ventana.obtener_render();
}

void display_text(std::string text, TTF_Font *font, SDL_Renderer *renderer, int w, int h) {
    SDL_Color white = {255, 255, 255, 255};
    Label label(w,
                h,
                text,
                font,
                white,
                renderer);
    label.setLabelText();
    label.draw();
}

void HighscoreWindow::show_highscores(SDL_Renderer *renderer, Fonts fonts) {
    Background background(BACKGROUND_IMAGE_ROOT, renderer,
                          1280, 720);
    SDL_Event e;
    int pressed = false;
    while (!pressed) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    pressed = true;
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();
        display_text("HIGHSCORES", fonts.getFont("wolfstein-title"), renderer, SCREEN_WIDTH / 4, 10);

        display_text("Top kills", fonts.getFont("wolfstein-subtitle"), renderer, SCREEN_WIDTH / 3,
                     50 + FONT_SIZE_TITLE);
        std::vector<std::pair<int, Jugador *>> topKills = ranking->obtenerTop5EnemigosMatados();
        int cantTopKills = topKills.size();
        for (int i = 0; i < cantTopKills; i++) {
            display_text("#" + std::to_string(i+1) + " - " + topKills.at(i).second->obtenerNombre() + " - " +
                         std::to_string(topKills.at(i).second->obtenerLogro().obtenerEnemigosMatados()),
                         fonts.getFont("wolfstein-names"), renderer,
                         SCREEN_WIDTH / 3,
                         70 + FONT_SIZE_TITLE + FONT_SIZE_SUBTITLE * i * 1.3);
        }

        display_text("Top score", fonts.getFont("wolfstein-subtitle"), renderer, SCREEN_WIDTH * 8 / 15,
                     50 + FONT_SIZE_TITLE);
        std::vector<std::pair<int, Jugador *>> topScore = ranking->obtenerTop5PuntosTotalesPorTesoros();
        int cantidadTopScore = topScore.size();
        for (int i = 0; i < cantidadTopScore; i++) {
            display_text("#" + std::to_string(i+1) + " - " + topScore.at(i).second->obtenerNombre() + " - " +
                         std::to_string(topScore.at(i).second->obtenerLogro().obtenerEnemigosMatados()),
                         fonts.getFont("wolfstein-names"), renderer,
                         SCREEN_WIDTH * 8 / 15,
                         70 + FONT_SIZE_TITLE + FONT_SIZE_SUBTITLE * i * 1.3);
        }

        display_text("Top shooter", fonts.getFont("wolfstein-subtitle"), renderer, SCREEN_WIDTH * 9 / 12,
                     50 + FONT_SIZE_TITLE);
        std::vector<std::pair<int, Jugador *>> topShooter = ranking->obtenerTop5BalasDisparadas();
        int cantTopShooter = topShooter.size();
        for (int i = 0; i < cantTopShooter; i++) {
            display_text("#" + std::to_string(i+1) + " - " + topShooter.at(i).second->obtenerNombre() + " - " +
                         std::to_string(topShooter.at(i).second->obtenerLogro().obtenerEnemigosMatados()),
                         fonts.getFont("wolfstein-names"), renderer,
                         SCREEN_WIDTH * 9 / 12,
                         70 + FONT_SIZE_TITLE + FONT_SIZE_SUBTITLE * i * 1.3);
        }

        SDL_RenderPresent(renderer);
    }
}

void HighscoreWindow::settearGanadores(Ranking &ran) {
    this->ranking = &ran;
}

/*
void HighscoreWindow::settearGanadores(std::vector<int>& ganadores,Player *jugador, std::map<int, Enemigo *> &enemigos){
    for (int i = 0; i < ganadores.size(); i++) {
        int id = ganadores[i];
        if (jugador->getId() == id) {
            int logro = jugador->getPuntaje();
            std::string puntaje = std::to_string(logro);
            this->ganadores.insert(std::make_pair(id, logro));

        } else {
            Enemigo *enemigo = enemigos.find(ganadores[i])->second;
            int logro = enemigo->getPuntaje();
            std::string puntaje = std::to_string(logro);
            this->ganadores.insert(std::make_pair(id, logro));
        }
    }
}*/
void HighscoreWindow::renderizar() {
    Background background(BACKGROUND_IMAGE_ROOT,
                          this->renderer, 1280, 720);
    background.drawBackground();
    while (1) {
        //SDL_Event e;
        show_highscores(this->renderer, this->fonts);
    }//CHQUEAR ESTE WHILE SE VA A RE COLGAR
}

HighscoreWindow::~HighscoreWindow() {
    this->ventana.cerrar();
    SDL_Quit();
}
