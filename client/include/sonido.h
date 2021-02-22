#ifndef SONIDO_H
#define SONIDO_H

#include <SDL2/SDL_mixer.h>
#include <string>

class Sonido {
private:
    Mix_Chunk *chunk;
    int canal;

public:
    /*
      * creara la clase sonido dejandola valida para uso
    */
    explicit Sonido(const std::string &archivo);

    /*
      * settea el volumen del sonido
    */
    void settearVolumen(int volume);

    /*
      * hace que el sonido suene
    */
    void play(int loops);

    /*
      * frena el sonido
    */
    void stop();

    /*
      * libera la clase sonido con sus recursos
    */
    ~Sonido();

};

#endif
