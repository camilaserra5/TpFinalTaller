#include <iostream>
#include <string>
#include "server.h"
#include "../common_src/socket.h"
#include "yaml-cpp/yaml.h"
#define OK_CODE 0
#define ERR_CODE 1
#define USAGE "Uso: ./server <config_file>"

int main(int argc, char *argv[]) {


    //YAML::Node config = YAML::LoadFile(argv[1]);
  //  const std::string port = config["port"].as<std::string>();

   Socket socket;
    if (socket.bind(argv[1]) != OK_CODE) {
        std::cout << "bind error";
        return ERR_CODE;
    }
    if (socket.listen() != OK_CODE) {
        std::cout << "listen error";
        return ERR_CODE;
    }
    Server server(std::move(socket));
    server.run();
    return OK_CODE;
}
