#include <iostream>
#include <string>
#include "client.h"
#include "../common_src/tcp_protocol.h"
#include <utility>
#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include "../common_src/SdlWindow.h"
#include "../common_src/SdlTexture.h"
#define END_LINE "\n"

Client::Client(Socket socket) : socket(std::move(socket)) {}

void Client::run() {
    try {
        SdlWindow window(800, 600);
        window.fill();
        // Usar factory
        SdlTexture im("cat.gif", window);
        Area srcArea(0, 0, 300, 300);
        bool running = true;
        int x = 100;
        int y = 150;
        while (running) {
            SDL_Event event;
            Area destArea(x, y, 300, 300);
            window.fill(); // Repinto el fondo gris
            im.render(srcArea, destArea);
            // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
            SDL_WaitEvent(&event);
            TCPProtocol::send(this->socket, event);
            switch(event.type) {
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT:
                            x -= 10;
                            break;
                        case SDLK_RIGHT:
                            x += 10;
                            break;
                        case SDLK_UP:
                            y -= 10;
                            break;
                        case SDLK_DOWN:
                            y += 10;
                            break;
                    }
                } // Fin KEY_DOWN
                    break;
                case SDL_MOUSEMOTION:
                    std::cout << "Oh! Mouse" << std::endl;
                    break;
                case SDL_QUIT:
                    std::cout << "Quit :(" << std::endl;
                    running = false;
                    break;
            }
            window.render();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

Client::~Client() {}
