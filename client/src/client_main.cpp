#include "../include/cliente.h"

#define OK_CODE 0
#define ERR_CODE 1

int main(int argc, char *argv[]) {
    Cliente client(reinterpret_cast<const char *>(1), reinterpret_cast<const char *>(2));
    client.run();
    return OK_CODE;
}