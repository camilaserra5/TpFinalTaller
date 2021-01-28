#ifndef THCLIENT_H
#define THCLIENT_H

#include <sstream>
#include <atomic>
#include "socket.h"
#include "thread.h"

class ThClient : public Thread {
private:
    std::stringstream mensaje_cliente;
    Socket socket;

    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;

    void procesar_pedido();

public:
    ThClient(Socket un_socket);

    /*
     * Atiende a un cliente. Procesa su pedido y le responde.
     */
    void run() override;

    /*
     * Indica si ya terminó de atenderse
     */
    bool is_dead();

    /*
     * corta con el proceso.
     */
    void stop();

    ~ThClient();
};

#endif /*THCLIENT_H*/
