#include "../include/logInWindow.h"
#include "../include/background.h"
#include "../include/label.h"
#include "comandos/crearPartida.h"
#include "comandos/unirseAPartida.h"
#include <config.h>

#define BACKGROUND_IMAGE IMGS_DIR BACKGROUND_IMG
#define WOLFSTEIN_TTF_ROOT FONTS_DIR WOLFENSTEIN_FONT
#define BACKGROUND_2_IMAGE_ROOT IMGS_DIR BACKGROUND2_IMG
#define FONT_SIZE 60
const SDL_Color white = {255, 255, 255, 255};
const SDL_Color red = {226, 106, 106, 255};

LogInWindow::LogInWindow(int screenWidth, int screenHeight, int screenWJuego) : screenWidth(screenWidth),
                                                                                screenHeight(screenHeight),
                                                                                screenWJuego(screenWJuego) {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    this->window = SDL_CreateWindow("Wolfstein 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->screenWidth,
                                    this->screenHeight, windowFlags);

    if (!this->window) {
        printf("Failed to open %d x %d window: %s\n", this->screenWidth, this->screenHeight, SDL_GetError());
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
    this->idCliente = -1;

}

void disp_text(std::string text, TTF_Font *font, SDL_Renderer *renderer, int w, int h, SDL_Color color) {
    Label label(w,
                h,
                text,
                font,
                color,
                renderer);
    label.setLabelText();
    label.draw();
}

void LogInWindow::start(SDL_Renderer *renderer, Fonts fonts) {
    Background background(BACKGROUND_IMAGE, renderer, this->screenWidth, this->screenHeight);
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
        disp_text("Press enter to start", fonts.getFont("wolfstein"), renderer, this->screenWidth / 3,
                  this->screenHeight / 2, white);
        SDL_RenderPresent(renderer);
    }
}

void
LogInWindow::connect(SDL_Renderer *renderer, Fonts fonts, std::string &ip, std::string &port, std::string &message) {
    Background background(BACKGROUND_IMAGE, renderer, this->screenWidth, this->screenHeight);
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
                        if (!ip.empty())
                            ip.erase(ip.size() - 1);
                    } else {
                        if (!port.empty())
                            port.erase(port.size() - 1);
                    }
                }
                if (e.key.keysym.sym == SDLK_UP) {
                    ipFinished = false;
                }
                if (e.key.keysym.sym == SDLK_DOWN) {
                    if (ip.empty()) {
                        message = "ip cannot be empty";
                    } else {
                        message = "";
                        ipFinished = true;
                    }
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    message = "";
                    if (ipFinished) {
                        if (port.empty()) {
                            message = "port cannot be empty";
                        } else {
                            portFinished = true;
                        }
                    }
                    if (ip.empty()) {
                        message = "ip cannot be empty";
                    } else {
                        ipFinished = true;
                    }
                }
            }
        }
        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();
        if (!ipFinished) {
            disp_text("--", fonts.getFont("wolfstein"), renderer,
                      (this->screenWidth / 3) - 40, this->screenHeight / 2, red);
        }
        disp_text("ip address: " + ip, fonts.getFont("wolfstein"), renderer,
                  this->screenWidth / 3, this->screenHeight / 2, white);
        if (ipFinished) {
            disp_text("--", fonts.getFont("wolfstein"), renderer,
                      (this->screenWidth / 3) - 40, this->screenHeight / 2 + FONT_SIZE, red);
        }
        disp_text("port: " + port, fonts.getFont("wolfstein"), renderer,
                  this->screenWidth / 3, this->screenHeight / 2 + FONT_SIZE, white);
        if (!message.empty()) {
            disp_text(message, fonts.getFont("wolfstein"), renderer, this->screenWidth / 3,
                      this->screenHeight / 2 + FONT_SIZE * 2, red);
        }
        SDL_RenderPresent(renderer);
    }
}

void LogInWindow::mostrarMenuPartidas(SDL_Renderer *renderer, Fonts fonts,
                                      std::vector<std::string> partidas, int &gameNumber) {
    Background background(BACKGROUND_2_IMAGE_ROOT, renderer, this->screenWidth, this->screenHeight);
    SDL_Event e;
    bool finished = false;
    int option = 0;
    while (!finished) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_DOWN) {
                    int cantPartidas = partidas.size();
                    if (!partidas.empty() && option <= cantPartidas) {
                        option++;
                    }
                }
                if (e.key.keysym.sym == SDLK_UP) {
                    if (option != 0)
                        option--;
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    gameNumber = option;
                    finished = true;
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();

        disp_text("Select an option:", fonts.getFont("wolfstein"), renderer, 10, 10, white);

        disp_text("New game", fonts.getFont("wolfstein"), renderer, FONT_SIZE,
                  2 * FONT_SIZE, white);
        int cantPartidas = partidas.size();
        for (int i = 1; i <= cantPartidas; i++) {
            disp_text(partidas[i - 1], fonts.getFont("wolfstein"),
                      renderer, FONT_SIZE,
                      2 * (i + 1) * FONT_SIZE, white);
        }

        disp_text("--", fonts.getFont("wolfstein"), renderer, FONT_SIZE - 40,
                  2 * (option + 1) * FONT_SIZE, red);

        SDL_RenderPresent(renderer);
    }
}

void LogInWindow::crearPartida(SDL_Renderer *renderer, Fonts fonts, std::string &param, int &option,
                               std::string &gameName, std::string &numberPlayers,
                               std::string &mapFile, std::string &playerName) {
    Background background(BACKGROUND_2_IMAGE_ROOT, renderer, this->screenWidth, this->screenHeight);
    SDL_Event e;
    bool finished = false;
    std::string message = "";
    while (!finished) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_DOWN) {
                    if (option != 3) {
                        if (!param.empty()) {
                            option++;
                            finished = true;
                            message = "";
                        } else {
                            message = "Please enter a valid value";
                        }
                    }
                }
                if (e.key.keysym.sym == SDLK_UP) {
                    if (option != 0) {
                        if (!param.empty()) {
                            option--;
                            finished = true;
                            message = "";
                        } else {
                            message = "Please enter a valid value";
                        }
                    }
                }
                if ((e.key.keysym.sym >= SDLK_ASTERISK && e.key.keysym.sym <= SDLK_SLASH) ||
                    (e.key.keysym.sym >= SDLK_COLON && e.key.keysym.sym <= SDLK_z)) {
                    if (option != 1) {
                        param += e.key.keysym.sym;
                    }
                }
                if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) {
                    param += e.key.keysym.sym;
                }
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    if (!param.empty()) {
                        param.erase(param.size() - 1);
                    }
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    if (!param.empty()) {
                        option++;
                        finished = true;
                        message = "";
                    } else {
                        message = "please enter a valid value";
                    }
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();

        disp_text("Creating new game!", fonts.getFont("wolfstein"), renderer, 10, 10, white);
        disp_text("Game name:" + gameName, fonts.getFont("wolfstein"), renderer, FONT_SIZE, 2 * FONT_SIZE, white);
        disp_text("Number of players:" + numberPlayers, fonts.getFont("wolfstein"), renderer, FONT_SIZE, 3 * FONT_SIZE,
                  white);
        disp_text("Map file:" + mapFile, fonts.getFont("wolfstein"), renderer, FONT_SIZE, 4 * FONT_SIZE, white);
        disp_text("Your name:" + playerName, fonts.getFont("wolfstein"), renderer, FONT_SIZE, 5 * FONT_SIZE, white);

        disp_text("--", fonts.getFont("wolfstein"), renderer, FONT_SIZE - 40,
                  2 + (option + 2) * FONT_SIZE, red);

        if (!message.empty()) {
            disp_text(message, fonts.getFont("wolfstein"), renderer, FONT_SIZE,
                      6 * FONT_SIZE, red);
        }

        SDL_RenderPresent(renderer);
    }
}

void LogInWindow::unirseAPartida(SDL_Renderer *renderer, Fonts fonts, std::string &nombre, std::string &playerName) {
    Background background(BACKGROUND_2_IMAGE_ROOT, renderer, this->screenWidth, this->screenHeight);
    SDL_Event e;
    bool finished = false;
    std::string message = "";
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
                    if (!nombre.empty()) {
                        finished = true;
                        message = "";
                    } else {
                        message = "Please enter a valid value";
                    }
                }
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();

        disp_text("Joining: " + nombre, fonts.getFont("wolfstein"), renderer, 10, 10, white);
        disp_text("Your name:" + playerName, fonts.getFont("wolfstein"), renderer, FONT_SIZE, 10 + 5 * FONT_SIZE,
                  white);
        disp_text("--", fonts.getFont("wolfstein"), renderer, FONT_SIZE - 40, 10 + 5 * FONT_SIZE, red);

        if (!message.empty()) {
            disp_text(message, fonts.getFont("wolfstein"), renderer, FONT_SIZE,
                      10 + 6 * FONT_SIZE, red);
        }

        SDL_RenderPresent(renderer);
    }
}


bool LogInWindow::pantallaEsperando(SDL_Renderer *renderer, Fonts fonts, Protocolo *protocolo) {
    Background background(BACKGROUND_2_IMAGE_ROOT, renderer, this->screenWidth, this->screenHeight);
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            }
        }

        SDL_Delay(16);
        SDL_RenderClear(renderer);
        background.drawBackground();

        disp_text("Esperando a los jugadores para comenzar", fonts.getFont("wolfstein"), renderer, 10, 10, white);

        SDL_RenderPresent(renderer);

        std::vector<char> serializado = protocolo->recibir();
        std::vector<char> sub(4);
        sub = std::vector<char>(&serializado[0], &serializado[4]);
        char number[4];
        memcpy(number, sub.data(), 4);
        uint32_t *buf = (uint32_t *) number;
        int idAccion = ntohl(*buf);
        return (idAccion == static_cast<int>(Accion::empezoPartida));
    }
}

void LogInWindow::pantallaError(SDL_Renderer *renderer, Fonts fonts, std::string &error) {
    Background background(BACKGROUND_IMAGE, renderer, this->screenWidth, this->screenHeight);
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

        disp_text("Error :(", fonts.getFont("wolfstein"), renderer, 10, 10, red);
        disp_text(error, fonts.getFont("wolfstein"), renderer, this->screenWidth / 4, 10 + 5 * FONT_SIZE, white);
        disp_text("Press enter to start over", fonts.getFont("wolfstein"), renderer, this->screenWidth / 4,
                  10 + 7 * FONT_SIZE, white);

        SDL_RenderPresent(renderer);
    }
}

void LogInWindow::run() {
    Background background(BACKGROUND_IMAGE, this->renderer, this->screenWidth, this->screenHeight);
    background.drawBackground();
    bool finished = false;
    while (!finished) {
        //  SDL_Event e;
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
        for (uint32_t i = 0; i < cantidadPartidas; i++) {
            memcpy(number, partidas.data() + j, 4);
            buf = (uint32_t *) number;
            uint32_t longNombre = ntohl(*buf);
            j += 4;
            std::string nombre;
            for (uint32_t k = 0; k < longNombre; k++) {
                nombre += partidas[j++];
            }
            std::ostringstream sstream;
            memcpy(number, partidas.data() + j, 4);
            buf = (uint32_t *) number;
            uint32_t available = ntohl(*buf);
            j += 4;
            memcpy(number, partidas.data() + j, 4);
            buf = (uint32_t *) number;
            uint32_t total = ntohl(*buf);
            j += 4;
            sstream << "Game No " << i + 1 << " - " << nombre << " " << available << "/" << total;
            partis.push_back(sstream.str());
            nombresPartidas.insert(std::make_pair(i, nombre));
        }

        int gameNumber;
        mostrarMenuPartidas(this->renderer, this->fonts, partis, gameNumber);

        if (gameNumber == 0) {
            // nueva partida
            std::string gameName;
            std::string numberPlayers;
            std::string mapFile;
            std::string playerName;
            int option = 0;
            while (option != 4) {
                switch (option) {
                    case 0:
                        crearPartida(this->renderer, this->fonts, gameName, option, gameName, numberPlayers, mapFile,
                                     playerName);
                        break;
                    case 1:
                        crearPartida(this->renderer, this->fonts, numberPlayers, option, gameName, numberPlayers,
                                     mapFile,
                                     playerName);
                        break;
                    case 2:
                        crearPartida(this->renderer, this->fonts, mapFile, option, gameName, numberPlayers, mapFile,
                                     playerName);
                        break;
                    case 3:
                        crearPartida(this->renderer, this->fonts, playerName, option, gameName, numberPlayers, mapFile,
                                     playerName);
                        break;
                }
            }


            CrearPartida crearPartida(-1, std::stoi(numberPlayers),
                                      gameName, mapFile, playerName, this->screenWJuego);
            std::vector<char> serializado = crearPartida.serializar();
            protocolo->enviar(serializado);
            std::vector<char> res = protocolo->recibir();
            char aux[4];
            memcpy(aux, res.data(), 4);
            uint32_t *buffer = (uint32_t *) aux;
            this->idCliente = ntohl(*buffer);
            if (((int) this->idCliente != -1) && (pantallaEsperando(this->renderer, this->fonts, protocolo))) {
                finished = true;
            } else {
                std::string error = "Sorry, there was an error!";
                pantallaError(this->renderer, this->fonts, error);
            }
        } else {
            // unirse a una existente
            std::string nombre = nombresPartidas.at(gameNumber - 1);
            std::string playerName;
            unirseAPartida(this->renderer, this->fonts, nombre, playerName);

            UnirseAPartida unirseAPartida(-1, nombre, playerName);
            std::vector<char> serializado = unirseAPartida.serializar();
            protocolo->enviar(serializado);
            std::vector<char> res = protocolo->recibir();
            char aux[4];
            memcpy(aux, res.data(), 4);
            uint32_t *buffer = (uint32_t *) aux;
            this->idCliente = ntohl(*buffer);
            if (((int) this->idCliente != -1) && (pantallaEsperando(this->renderer, this->fonts, protocolo))) {
                finished = true;
            } else {
                std::string error = "Sorry, there was an error!";
                pantallaError(this->renderer, this->fonts, error);
            }
        }
    }
    SDL_DestroyRenderer(this->renderer);

    SDL_DestroyWindow(this->window);
}

LogInWindow::~LogInWindow() {

}
