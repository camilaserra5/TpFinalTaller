#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "../common_src/socket.h"

/**
 * The client.
 */
class Client {
public:
    /**
     * Creates the client with the socket connection.
     * @param socket: the client socket, has to be already connected
     */
    explicit Client(Socket socket);

    /**
     * Reads from stdin until EOF and sends all to the server.
     * Closes write connection.
     * Waits for a response, and prints it on stdout.
     * Closes read connection.
     */
    void run();

    /**
     * Client destructor.
     */
    ~Client();

private:
    Socket socket;

    void sendStdInputToServer();
};

#endif //CLIENT_H
