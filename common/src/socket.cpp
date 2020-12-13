#include <iostream>
#include <unistd.h>
#include <cstring>
#include "../include/socket.h"

Socket::Socket(int fd) {
    this->fd = fd;
}

Socket::Socket() {
    this->fd = -1;
}

bool Socket::valid() {
    return this->fd != -1;
}

Socket::Socket(Socket &&socket) {
    this->fd = socket.fd;
    socket.fd = -1;
}

Socket &Socket::operator=(Socket &&socket) {
    this->fd = socket.fd;
    socket.fd = -1;
    return *this;
}

Socket::Socket(char *host, char *port) {
    struct addrinfo hints;
    struct addrinfo *addr_info;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(NULL, port, &hints, &addr_info) != 0) {
        throw std::runtime_error("Error in getaddrinfo");
    }

    int temp_fd = -1;
    bool cont = true;
    struct addrinfo *addr = addr_info;
    while (addr && cont) {
        temp_fd = ::socket(addr->ai_family,
                           addr->ai_socktype,
                           addr->ai_protocol);
        if (::connect(temp_fd, addr->ai_addr, addr->ai_addrlen) == -1) {
            cont = false;
        }
        addr = addr->ai_next;
    }

    this->fd = temp_fd;
    freeaddrinfo(addr_info);
    if (!valid()) {
        throw std::runtime_error("Error while trying to connect");
    }
}

int Socket::bind(char *port) {
    struct addrinfo hints;
    struct addrinfo *addr_info;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(NULL, port, &hints, &addr_info) != 0) {
        return -1;
    }

    int temp_fd = -1;
    bool cont = true;
    struct addrinfo *addr = addr_info;
    while (addr && cont) {
        temp_fd = ::socket(addr->ai_family,
                           addr->ai_socktype,
                           addr->ai_protocol);
        if (::bind(temp_fd, addr->ai_addr, addr->ai_addrlen) == -1) {
            cont = false;
        }
        addr = addr->ai_next;
    }

    this->fd = temp_fd;
    freeaddrinfo(addr_info);
    return this->fd == -1;
}

int Socket::listen() {
    return ::listen(this->fd, MAX_CONNECTIONS) != 0;
}

int Socket::getFd() {
    return this->fd;
}

Socket Socket::accept() {
    int fd = ::accept(this->fd, nullptr, nullptr);
    if (fd == -1) {
        return Socket();
    }
    return Socket(fd);
}

void Socket::shutdown() {
    ::shutdown(this->fd, SHUT_WR);
    ::shutdown(this->fd, SHUT_RD);
}

void Socket::closeWrite() {
    ::shutdown(this->fd, SHUT_WR);
}

void Socket::closeRead() {
    ::shutdown(this->fd, SHUT_RD);
}

Socket::~Socket() {
    if (this->fd != -1) {
        ::shutdown(this->fd, SHUT_RDWR);
        ::close(this->fd);
    }
}
