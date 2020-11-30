#include <iostream>
#include <utility>
#include <sstream>
#include <cstring>
#include <string>
#include "../include/client_processor.h"
#include "../common_src/include/tcp_protocol.h"

#define BUFF_SIZE 64

ClientProcessor::ClientProcessor(Socket socket, std::queue<SDL_Event> queue) :
        socket(std::move(socket)), eventQueue(queue){
    this->is_alive = true;
}

void ClientProcessor::run() {
    std::string protocolStr = TCPProtocol::receive(this->socket);

    TCPProtocol::send(this->socket, resp);
    this->socket.closeRead();
    this->socket.closeWrite();
    this->is_alive = false;
}

bool ClientProcessor::isAlive() {
    return this->is_alive;
}

ClientProcessor::~ClientProcessor() {}
