#ifndef SONIDO_H
#define SONIDO_H

#include <SDL2/SDL_mixer.h>
#include <string>

class Sonido {
private:
    Mix_Chunk* chunk;
    int channel;

public:
    explicit Sonido(const std::string& file);
    void settearVolumen(int volume);
    void play(int loops = 0);
    void stop();
    ~Sonido();

};

#endif
