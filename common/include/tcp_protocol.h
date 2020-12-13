#ifndef TCP_PROTOCOL_H
#define TCP_PROTOCOL_H

#include <string>
#include "socket.h"

/**
 * The TCP Protocol. Sends and receives messages through a socket connection.
 */
namespace TCPProtocol {
    /**
     * Sends the @message
     * @param socket: the socket connection
     * @param message: the message to be sent
     */
    void send(Socket &socket, std::string message);

    /**
     * Receives a message
     * @param socket: the socket connection
     * @return the message received
     */
    std::string receive(Socket &socket);
}

#endif //TCP_PROTOCOL_H
