#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include "client_manager.h"

#define BASE_PATH "/"

ClientManager::ClientManager(Socket socket) :
        socket(std::move(socket)) {
}

void ClientManager::run() {
    Socket client;
    while ((client = this->socket.accept()).valid()) {
        this->clients.push_back(new ClientProcessor(std::move(client), eventQueue));
        this->clients.back()->start();
        for (unsigned int i = 0; i < this->clients.size(); i++) {
            if (!this->clients[i]->isAlive()) {
                this->clients[i]->join();
                delete this->clients[i];
                this->clients.erase(this->clients.begin() + i);
            }
        }
    }
}

void ClientManager::stop() {
    this->socket.shutdown();
    for (ClientProcessor *cli : this->clients) {
        cli->join();
        delete cli;
    }
}

ClientManager::~ClientManager() {}
