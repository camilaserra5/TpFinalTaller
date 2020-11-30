#include "../include/protected_queue.h"

ProtectedQueue::ProtectedQueue(){

}
ProtectedQueue::~ProtectedQueue(){

}
SDL_Event ProtectedQueue::obtener_evento(){
  std::lock_guard<std::mutex> l(this->m);
  SDL_Event evento =  this->cola_eventos.front();
  this->cola_eventos.pop();
  return evento;
}
void ProtectedQueue::aniadir_evento(SDL_Event event){
  std::lock_guard<std::mutex> l(this->m);
  this->cola_eventos.push(event);
}
