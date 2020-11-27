#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "../common_src/socket.h"
#include "client_manager.h"

/**
 * The server.
 */
class Server {
public:
    /**
     * Creates the server.
     * @param socket: a server socket already listening
     * @param rootFile: the path of the root file
     */
    Server(Socket socket);

    /**
     * Runs the server until the exit character is received.
     */
    void run();

    /**
     * Server destructor.
     */
    ~Server();

private:
    ClientManager clientManager;
};

#endif //SERVER_H
