#include <iostream>
#include <string>
#include <utility>
#include "server.h"

Server::Server(Socket socket) :
        clientManager(std::move(socket)) {
    this->clientManager.start();
}

void Server::run() {
    while (std::cin.get() != 'q') {
    }
    this->clientManager.stop();
    this->clientManager.join();
}

Server::~Server() {}
