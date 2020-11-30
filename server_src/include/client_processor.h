#ifndef CLIENT_PROCESSOR_H
#define CLIENT_PROCESSOR_H

#include "../common_src/include/socket.h"
#include "../common_src/include/thread.h"
#include <SDL2/SDL.h>
#include <string>
#include <queue>
/**
 * The client processor.
 * In charge of processing an individual client.
 */
class ClientProcessor : public Thread {
public:
    /**
     * Creates the processor
     * @param socket: the socket corresponding to the connection with a client
     * @param resourceList
     */
    ClientProcessor(Socket socket,std::queue<SDL_Event>& eventQueue);

    /**
     * Processes the protocol received.
     * Sends the response to the client.
     * Closes the connection.
     */
    void run() override;

    /**
     * @return true while still processing. false, when already done.
     */
    bool isAlive();

    /**
     * Client processor destructor.
     */
    ~ClientProcessor() override;

private:
    Socket socket;

    bool is_alive;
    std::queue<SDL_Event> eventQueue;
};

#endif //CLIENT_PROCESSOR_H
