#include "../include/sonido.h"

Sonido::Sonido(const std::string &archivo) {
    chunk = Mix_LoadWAV(archivo.c_str());
    if (!chunk) {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
    this->canal = -1;
}

void Sonido::play(int loops) {
    if (!Mix_Playing(this->canal))
        this->canal = Mix_PlayChannel(-1, this->chunk, loops);
}

void Sonido::settearVolumen(int volume) {
    Mix_VolumeChunk(this->chunk, volume);
}

void Sonido::stop() {
    Mix_FadeOutChannel(this->canal, 1000);
}

Sonido::~Sonido() {
    Mix_FreeChunk(this->chunk);
}