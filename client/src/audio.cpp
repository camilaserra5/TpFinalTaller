#include "../include/audio.h"

#include <stdexcept>

Audio::Audio() {
    if ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        throw std::runtime_error("No se puede abrir audio");
}

Audio::~Audio(){
    Mix_CloseAudio();
}
