#include "../include/musica.h"
#include <stdexcept>

Musica::Musica(const std::string &archivo) {
    this->musicaPtr = Mix_LoadMUS(archivo.c_str());

    if (musicaPtr == NULL)
        throw std::runtime_error("Fallo al abrir archivo de musica");
}

void Musica::play(int loop) {
    Mix_PlayMusic(this->musicaPtr, loop);
}

Musica::~Musica() {
    Mix_FreeMusic(this->musicaPtr);
    this->musicaPtr = NULL;
}
