#ifndef SONIDO_H
#define SONIDO_H

#include <SDL2/SDL_mixer.h>
#include <string>

class Sonido {
private:
    Mix_Chunk *chunk;
    int canal;

public:
    explicit Sonido(const std::string &archivo);

    void settearVolumen(int volume);

    void play(int loops);

    void stop();

    ~Sonido();

};

#endif
