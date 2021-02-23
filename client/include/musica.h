#ifndef WOLFSTEIN_MUSICA_H
#define WOLFSTEIN_MUSICA_H

#include <SDL2/SDL_mixer.h>
#include <string>

class Musica {
private:
    Mix_Music *musicaPtr;

public:
    /*
      * creara la clase musica dejandola valida para uso
    */
    explicit Musica(const std::string &archivo);

    /*
      * hace que suene la musica
    */
    void play(int loop);

    /*
      * liberara la clase musica con sus recursos
    */
    /*
      * frena la musica;
    */
    void stop();
    /*
      * libera la musica
    */  
    ~Musica();
};

#endif //WOLFSTEIN_MUSICA_H
