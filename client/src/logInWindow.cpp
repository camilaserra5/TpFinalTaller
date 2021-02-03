#include "../include/logInWindow.h"
#include "../include/scene.h"
#include "../include/background.h"
#include "SDL2/SDL_ttf.h"
#include "../include/label.h"
#include <sstream>
#include <protocolo.h>

#define WOLFSTEIN_TTF_ROOT "../../resources/fuentes/wolfenstein.ttf"
#define BACKGROUND_IMAGE_ROOT "../../client/resources/images/background.png"

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

    fonts.addFont("wolfstein", WOLFSTEIN_TTF_ROOT, 60);

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
                      SCREEN_HEIGHT * 3 / 6);
            disp_text("port: " + port, fonts.getFont("wolfstein"), this->renderer, SCREEN_WIDTH / 3,
                      SCREEN_HEIGHT * 4 / 6);
            if (step >= 2) {
                disp_text(socket_text, fonts.getFont("wolfstein"), this->renderer, SCREEN_WIDTH / 3,
                          SCREEN_HEIGHT * 5 / 6);
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
        Protocolo protocolo(std::move(socket));
        this->protocolo = std::move(protocolo);
        std::cout << "recibo partidas";
        std::vector<char> partidas = protocolo.recibir();
        std::vector<std::string> partis;
        char cantidadPartidas = partidas[0];
        int j = 1;
        for (int i = 0; i < cantidadPartidas; i++) {
            std::string nombre;
            for (int k = 0; k < partidas[j]; k++) {
                nombre += partidas[++j];
            }
            partis.push_back("Partida:" + nombre + " " + partidas[++j] + "/" + partidas[++j]);
        }

        int conti = true;
        while (conti) {
            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    exit(0);
                } else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_n) {
                    }
                }
            }

            SDL_Delay(16);
            SDL_RenderClear(renderer);
            background.drawBackground();

            disp_text("Press N to create a new game", fonts.getFont("wolfstein"), this->renderer, SCREEN_WIDTH / 3,
                      SCREEN_HEIGHT / 6);


            disp_text(partis.front(), fonts.getFont("wolfstein"),
                      this->renderer, SCREEN_WIDTH / 3,
                      SCREEN_HEIGHT * 3 / 6);


            SDL_RenderPresent(renderer);
        }

    }

}

LogInWindow::~LogInWindow() {
    SDL_DestroyRenderer(this->renderer);

    SDL_DestroyWindow(this->window);

    SDL_Quit();
}
