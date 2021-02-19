#include "../include/cliente.h"
#include "../include/logInWindow.h"

#define OK_CODE 0
#define ERR_CODE 1

int main(int argc, char *argv[]) {
    std::string path = "";
    if (argc > 1)
        path = argv[1];
    Cliente client(path);
    client.run();
    return OK_CODE;
}
