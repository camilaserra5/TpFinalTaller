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

    }
}

void ClientManager::stop() {
    this->socket.shutdown();

}

ClientManager::~ClientManager() {}
