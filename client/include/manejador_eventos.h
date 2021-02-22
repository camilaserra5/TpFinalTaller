#ifndef _MANEJADOR_EVENTOS_H
#define _MANEJADOR_EVENTOS_H

#include "thread.h" // porque por un hilo se esta dibujando y por el otro se va manejando los eventos, no es algo secuencial
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include "blocking_queue.h"
#include "comandos/comando.h"
#include "sonido.h"
#include <atomic>

class ManejadorEventos : public Thread {
public:
    /*
      * creara la clase manejador de eventos dejandola valida para uso
      * la cola bloqueanda debera estar inicializada
    */
    ManejadorEventos(int &id, BlockingQueue<Comando *> &eventos);
    /*
      * liberara la clase junto a sus recursos
    */
    ~ManejadorEventos();
    /*
      * ejecuta el loop de eventos
    */
    void run() override;
    /*
      * se encarga de detectar los eventos que le llega por consola
    */
    void detectarEventos(SDL_Event &event);
    /*
      * cierra el loop de eventos
    */
    void stop();
    /*
      * crea el comando movimiento y lo mete a la cola de comandos
    */
    void crearMovimiento(Accion direccion);
    /*
      * devuelve si el hilo esta vivo
    */
    bool esta_vivo();
    /*
      * creara el comando ataque y lo mete en la cola de comandos
    */
    void crearAtaque();
    /*
      * creara el comando apertura de puertas y lo mete en la cola de comandos
    */
    void crearAperturaDePuerta();
    /*
      * creara el comando cambio de arma y lo metera en la cola de comandos
    */  
    void crearCambioDeArma();

private:
    int idJugador;
    BlockingQueue<Comando *> &eventos;
    std::atomic<bool> corriendo;
    Sonido sonidoAmbiente;
};

#endif
