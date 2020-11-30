#ifndef  _PROTECTED_QUEUE_
#define _PROTECTED_QUEUE_
#include <queue>
#include <mutex>
#include <SDL2/SDL.h>
#include <exception>

class QueueException: public std::exception{
  private:
    std::string error;
  public:
    explicit QueueException(const std::string& error):
    error(error)
    {}
    //const std::string getError() const { return this->error;}
};

class ProtectedQueue{
  private:
    std::queue<SDL_Event> cola_eventos;
    std::mutex m;
  public:
    ProtectedQueue();
    ~ProtectedQueue();
    SDL_Event obtener_evento();
    void aniadir_evento(SDL_Event event);
};
#endif
