#include "../include/logInWindow.h"
#include "../include/scene.h"
#include "../include/background.h"
#include "SDL2/SDL_ttf.h"
#include "../include/label.h"
#include <sstream>
#include "protocolo.h"
#include "comandos/crearPartida.h"
#include "comandos/unirseAPartida.h"


#define WOLFSTEIN_TTF_ROOT "../../resources/fuentes/wolfenstein.ttf"
#define BACKGROUND_IMAGE_ROOT "../../client/resources/images/background.png"
#define BACKGROUND_2_IMAGE_ROOT "../../client/resources/images/background2.jpg"
#define FONT_SIZE 60

LogInWindow::LogInWindow() {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    this->window = SDL_CreateWindow("Wolfstein 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, windowFlags);

    if (!this->window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    if (TTF_Init() == -1) {
        printf("Failed to init TTF\n");
        exit(1);
    }

    fonts.addFont("wolfstein", WOLFSTEIN_TTF_ROOT, FONT_SIZE);

    this->renderer = SDL_CreateRenderer(this->window, -1, rendererFlags);

    if (!this->renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

}

void disp_text(std::string text, TTF_Font *font, SDL_Renderer *renderer, int w, int h) {
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

void start(SDL_Renderer *renderer, Fonts fonts) {
    Background background(BACKGROUND_IMAGE_ROOT, renderer);
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
        disp_text("Press enter to start", fonts.getFont("wolfstein"), renderer, SCREEN_WIDTH / 3,
                  SCREEN_HEIGHT / 2);
        SDL_RenderPresent(renderer);
    }
}

void connect(SDL_Renderer *renderer, Fonts fonts, std::string &ip, std::string &port, std::string &message) {
    Background background(BACKGROUND_IMAGE_ROOT, renderer);
    SDL_Event e;
    bool ipFinished = false;
    bool portFinished = false;
    while (!ipFinished || !portFinished) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if ((e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) ||
                    e.key.keysym.sym == SDLK_PERIOD) {
                    if (!ipFinished) {
                        ip += e.key.keysym.sym;
                    } else {
                        port += e.key.keysym.sym;
                    }
                }
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    if (!ipFinished) {
                        ip.erase(ip.size() - 1);
                    } else {
                        port.erase(port.size() - 1);
                    }
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    if (ipFinished) {
                        portFinished = true;
                    }
                    ipFinished = true;
                }
            }
        }
        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();
        disp_text("ip address: " + ip, fonts.getFont("wolfstein"), renderer,
                  SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2);
        disp_text("port: " + port, fonts.getFont("wolfstein"), renderer,
                  SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2 + FONT_SIZE);
        if (!message.empty()) {
            disp_text(message, fonts.getFont("wolfstein"), renderer, SCREEN_WIDTH / 3,
                      SCREEN_HEIGHT / 2 + FONT_SIZE * 2);
        }
        SDL_RenderPresent(renderer);
    }
}

void mostrarMenuPartidas(SDL_Renderer *renderer, Fonts fonts,
                         std::vector<std::string> partidas, std::string &gameNumber) {
    Background background(BACKGROUND_2_IMAGE_ROOT, renderer);
    SDL_Event e;
    bool finished = false;
    while (!finished) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_n) {
                    gameNumber = "";
                    finished = true;
                }
                if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) {
                    gameNumber += e.key.keysym.sym;
                }
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    gameNumber.erase(gameNumber.size() - 1);
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    int i = std::stoi(gameNumber);
                    if (i > 0 && i < partidas.size())
                        finished = true;
                    else gameNumber = "";
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();

        disp_text("Press N to create a new game", fonts.getFont("wolfstein"), renderer, 10, 10);
        disp_text("or the corresponding game number + enter to join:", fonts.getFont("wolfstein"), renderer, 10,
                  10 + FONT_SIZE);

        for (int i = 1; i <= partidas.size(); i++) {
            disp_text(partidas[i - 1], fonts.getFont("wolfstein"),
                      renderer, FONT_SIZE,
                      10 + FONT_SIZE + (FONT_SIZE * i));
        }

        SDL_RenderPresent(renderer);
    }
}

void crearPartida(SDL_Renderer *renderer, Fonts fonts, std::string &param,
                  std::string &gameName, std::string &numberPlayers,
                  std::string &mapFile, std::string &playerName) {
    Background background(BACKGROUND_2_IMAGE_ROOT, renderer);
    SDL_Event e;
    bool finished = false;
    while (!finished) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if ((e.key.keysym.sym >= SDLK_ASTERISK && e.key.keysym.sym <= SDLK_z)) {
                    param += e.key.keysym.sym;
                }
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    param.erase(param.size() - 1);
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    finished = true;
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();

        disp_text("Creating new game!", fonts.getFont("wolfstein"), renderer, 10, 10);
        disp_text("Game name:" + gameName, fonts.getFont("wolfstein"), renderer, 10, 10 + 2 * FONT_SIZE);
        disp_text("Number of players:" + numberPlayers, fonts.getFont("wolfstein"), renderer, 10, 10 + 3 * FONT_SIZE);
        disp_text("Map file:" + mapFile, fonts.getFont("wolfstein"), renderer, 10, 10 + 4 * FONT_SIZE);
        disp_text("Your name:" + playerName, fonts.getFont("wolfstein"), renderer, 10, 10 + 5 * FONT_SIZE);

        SDL_RenderPresent(renderer);
    }
}

void unirseAPartida(SDL_Renderer *renderer, Fonts fonts, std::string &nombre, std::string &playerName) {
    Background background(BACKGROUND_2_IMAGE_ROOT, renderer);
    SDL_Event e;
    bool finished = false;
    while (!finished) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if ((e.key.keysym.sym >= SDLK_ASTERISK && e.key.keysym.sym <= SDLK_z)) {
                    playerName += e.key.keysym.sym;
                }
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    playerName.erase(playerName.size() - 1);
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    finished = true;
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();

        disp_text("Joining: " + nombre, fonts.getFont("wolfstein"), renderer, 10, 10);
        disp_text("Your name:" + playerName, fonts.getFont("wolfstein"), renderer, 10, 10 + 5 * FONT_SIZE);

        SDL_RenderPresent(renderer);
    }
}


void pantallaEsperando(SDL_Renderer *renderer, Fonts fonts) {
    Background background(BACKGROUND_2_IMAGE_ROOT, renderer);
    SDL_Event e;
    bool finished = false;
    while (!finished) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    finished = true;
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();

        disp_text("Esperando a los jugadores para comenzar", fonts.getFont("wolfstein"), renderer, 10, 10);

        SDL_RenderPresent(renderer);
    }
}

void pantallaError(SDL_Renderer *renderer, Fonts fonts, std::string &error) {
    Background background(BACKGROUND_2_IMAGE_ROOT, renderer);
    SDL_Event e;
    bool finished = false;
    while (!finished) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    finished = true;
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();

        disp_text("Error :(", fonts.getFont("wolfstein"), renderer, 10, 10);
        disp_text(error, fonts.getFont("wolfstein"), renderer, 10, 10 + 5 * FONT_SIZE);

        SDL_RenderPresent(renderer);
    }
}

void LogInWindow::run() {
    Background background(BACKGROUND_IMAGE_ROOT, this->renderer);
    background.drawBackground();
    while (1) {
        SDL_Event e;
        start(this->renderer, this->fonts);

        std::string ip;
        std::string port;
        std::string message;
        bool connected = false;
        while (!connected) {
            connect(this->renderer, this->fonts, ip, port, message);
            try {
                this->socket.conectar(ip.c_str(), port.c_str());
                connected = true;
            } catch (std::exception &exc) {
                message = "Error connecting, try again";
                ip = "";
                port = "";
            }
        }

        this->protocolo = new Protocolo(std::move(socket));
        std::vector<char> partidas = protocolo->recibir();
        std::vector<std::string> partis;
        std::map<int, std::string> nombresPartidas;

        char number[4];
        memcpy(number, partidas.data(), 4);
        uint32_t *buf = (uint32_t *) number;
        uint32_t cantidadPartidas = ntohl(*buf);

        int j = 4;
        for (int i = 0; i < cantidadPartidas; i++) {
            memcpy(number, partidas.data() + j, 4);
            buf = (uint32_t *) number;
            uint32_t longNombre = ntohl(*buf);
            j += 4;
            std::string nombre;
            for (int k = 0; k < longNombre; k++) {
                nombre += partidas[j++];
            }
            std::ostringstream sstream;
            memcpy(number, partidas.data() + j, 4);
            buf = (uint32_t *) number;
            j += 4;
            memcpy(number, partidas.data() + j, 4);
            buf = (uint32_t *) number;
            j += 4;
            sstream << "Game No " << i + 1 << " - " << nombre << " " << ntohl(*buf) << "/" << ntohl(*buf);
            partis.push_back(sstream.str());
            nombresPartidas.insert(std::make_pair(i, nombre));
        }

        std::string gameNumber;
        mostrarMenuPartidas(this->renderer, this->fonts, partis, gameNumber);

        if (gameNumber.empty()) {
            // nueva partida
            std::string gameName;
            std::string numberPlayers;
            std::string mapFile;
            std::string playerName;

            crearPartida(this->renderer, this->fonts, gameName, gameName, numberPlayers, mapFile, playerName);
            crearPartida(this->renderer, this->fonts, numberPlayers, gameName, numberPlayers, mapFile, playerName);
            crearPartida(this->renderer, this->fonts, mapFile, gameName, numberPlayers, mapFile, playerName);
            crearPartida(this->renderer, this->fonts, playerName, gameName, numberPlayers, mapFile, playerName);

            CrearPartida crearPartida(-1, std::stoi(numberPlayers),
                                      gameName, mapFile, playerName);
            std::vector<char> serializado = crearPartida.serializar();
            protocolo->enviar(serializado);
            std::vector<char> res = protocolo->recibir();
            bool pudoCrearPartida = res[0];
            if (!pudoCrearPartida) {
                std::string error = "Error creando partida";
                pantallaError(this->renderer, this->fonts, error);
            }
            pantallaEsperando(this->renderer, this->fonts);
        } else {
            // unirse a una existente
            std::string nombre = nombresPartidas.at(std::stoi(gameNumber) - 1);
            std::string playerName;
            unirseAPartida(this->renderer, this->fonts, nombre, playerName);

            UnirseAPartida unirseAPartida(-1, nombre, playerName);
            std::vector<char> serializado = unirseAPartida.serializar();
            protocolo->enviar(serializado);
            std::vector<char> res = protocolo->recibir();
            bool pudoUnirse = res[0];
            if (!pudoUnirse) {
                std::string error = "Error uniendose a partida";
                pantallaError(this->renderer, this->fonts, error);
            }
            pantallaEsperando(this->renderer, this->fonts);
        }
    }
}

LogInWindow::~LogInWindow() {
    SDL_DestroyRenderer(this->renderer);

    SDL_DestroyWindow(this->window);

    SDL_Quit();
}
