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

void LogInWindow::run() {
    Background background(BACKGROUND_IMAGE_ROOT, this->renderer);
    background.drawBackground();
    while (1) {
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
            disp_text("Press enter to start", fonts.getFont("wolfstein"), this->renderer, SCREEN_WIDTH / 3,
                      SCREEN_HEIGHT / 2);
            SDL_RenderPresent(renderer);
        }

        std::string ip;
        std::string port;
        std::string socket_text = "Connecting...";
        int step = 0;
        while (step < 4) {
            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    exit(0);
                } else if (e.type == SDL_KEYDOWN) {
                    if ((e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) ||
                        e.key.keysym.sym == SDLK_PERIOD) {
                        if (step == 0) {
                            ip += e.key.keysym.sym;
                        } else {
                            port += e.key.keysym.sym;
                        }
                    }
                    if (e.key.keysym.sym == SDLK_BACKSPACE) {
                        if (step == 0) {
                            ip.erase(ip.size() - 1);
                        } else {
                            port.erase(ip.size() - 1);
                        }
                    }
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        step++;
                        if (step > 3)
                            step = 0;
                    }
                }
            }
            SDL_Delay(16);
            SDL_RenderClear(renderer);
            background.drawBackground();
            disp_text("ip address: " + ip, fonts.getFont("wolfstein"), this->renderer, SCREEN_WIDTH / 3,
                      SCREEN_HEIGHT / 2);
            disp_text("port: " + port, fonts.getFont("wolfstein"), this->renderer, SCREEN_WIDTH / 3,
                      SCREEN_HEIGHT / 2 + FONT_SIZE);
            if (step >= 2) {
                disp_text(socket_text, fonts.getFont("wolfstein"), this->renderer, SCREEN_WIDTH / 3,
                          SCREEN_HEIGHT / 2 + FONT_SIZE * 2);
            }
            SDL_RenderPresent(renderer);
            if (step == 2) {
                try {
                    this->socket.conectar(ip.c_str(), port.c_str());
                    step = 4;
                } catch (std::exception &exc) {
                    socket_text = "Error connecting, press enter to start again";
                    ip = "";
                    port = "";
                    step++;
                }
            }
        }

        this->protocolo = new Protocolo(std::move(socket));
        std::cout << "recibo partidas";
        std::vector<char> partidas = protocolo->recibir();
        std::vector<std::string> partis;
        char cantidadPartidas = partidas[0];
        int j = 1;
        for (int i = 0; i < cantidadPartidas; i++) {
            std::string nombre;
            for (int k = 0; k < partidas[j]; k++) {
                nombre += partidas[++j];
            }
            std::ostringstream sstream;
            sstream << "Game No " << i + 1 << " - " << nombre << " " << (char)partidas[++j] << "/" << (char)partidas[++j];
            partis.push_back(sstream.str());
        }

        Background background2(BACKGROUND_2_IMAGE_ROOT, this->renderer);
        int conti = true;
        std::string gameNo;
        while (conti) {
            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    exit(0);
                } else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_n) {
                      CrearPartida crearPartida(-1,8,"wolfstein","ruta","nombre");//parametros ingresados!
                      std::vector<char> serializado = crearPartida.serializar();
                      protocolo->enviar(serializado);
                    }
                    if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) {
                        gameNo += e.key.keysym.sym;
                    }
                    if (e.key.keysym.sym == SDLK_BACKSPACE) {
                        gameNo.erase(gameNo.size() - 1);
                    }
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        int i = std::stoi(gameNo);
                        if (i > 0 && i < partis.size())
                            conti = false;
                        else gameNo = "";
                    }
                }
            }

            SDL_Delay(16);
            SDL_RenderClear(renderer);

            background2.drawBackground();

            disp_text("Press N to create a new game", fonts.getFont("wolfstein"), this->renderer, 10, 10);
            disp_text("or the corresponding game number + enter to join:", fonts.getFont("wolfstein"), this->renderer,
                      10,
                      10 + FONT_SIZE);

            for (int i = 1; i <= partis.size(); i++) {
                disp_text(partis[i - 1], fonts.getFont("wolfstein"),
                          this->renderer, FONT_SIZE,
                          10 + FONT_SIZE + (FONT_SIZE * i));
            }

            SDL_RenderPresent(renderer);
        }

        conti = true;
        while (conti) {
            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    exit(0);
                } else if (e.type == SDL_KEYDOWN) {

                }
            }

            SDL_Delay(16);
            SDL_RenderClear(renderer);

            background2.drawBackground();

            disp_text("Joining game no " + gameNo, fonts.getFont("wolfstein"), this->renderer, 10, 10);
            SDL_RenderPresent(renderer);
        }


    }

}

LogInWindow::~LogInWindow() {
    SDL_DestroyRenderer(this->renderer);

    SDL_DestroyWindow(this->window);

    SDL_Quit();
}
