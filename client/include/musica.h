#ifndef WOLFSTEIN_MUSICA_H
#define WOLFSTEIN_MUSICA_H

#include <SDL2/SDL_mixer.h>
#include <string>

class Musica {
private:
    Mix_Music* musicaPtr;

public:
    explicit Musica(const std::string& archivo);
    void play(int loop);
    ~Musica();
};

#endif //WOLFSTEIN_MUSICA_H
