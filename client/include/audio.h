#ifndef WOLFSTEIN_AUDIO_H
#define WOLFSTEIN_AUDIO_H

#include <SDL2/SDL_mixer.h>

class Audio {
public:
    /*
      * crea el audio dejandolo valido para uso
    */
    Audio();

    /*
      * libera la clase audio
    */
    ~Audio();
};

#endif //WOLFSTEIN_AUDIO_H
