#ifndef SOCKET_H
#define SOCKET_H

#include <netdb.h>
#include <sys/socket.h>

/**
 * The socket.
 */
class Socket {
    static const int MAX_CONNECTIONS = 20;

public:
    explicit Socket(int fd);

    Socket();

    Socket(Socket &&socket);

    Socket &operator=(Socket &&socket);

    /**
     * Creates the client socket with the given parameters.
     * The Socket will be already connected.
     * If unable to connect, and exception will be thrown.
     * @param host
     * @param port
     */
    Socket(char *host, char *port);

    /**
     * Binds the socket
     * @param port: the port
     * @return 0 if OK
     */
    int bind(char *port);

    /**
     * Starts listening to accept connections on the socket fd.
     * @return 0 if OK
     */
    int listen();

    /**
     * @return true if the socket is in a valid state.
     */
    bool valid();

    /**
     * @return the socket fd.
     */
    int getFd();

    /**
     * Accepts a connection on the fd.
     * Opens a new socket for this connection
     * @return the new socket
     */
    Socket accept();

    /**
     * Shuts down the reception and the transmissions.
     */
    void shutdown();

    /**
     * Shuts down the transmissions of the socket fd.
     */
    void closeWrite();

    /**
     * Shuts down the receptions of the socket fd.
     * Shut down all or part of the connection open on socket FD.
     */
    void closeRead();

    /**
     * Socket destructor.
     */
    ~Socket();

private:
    int fd;
};

#endif //SOCKET_H
