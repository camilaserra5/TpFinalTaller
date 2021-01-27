#include "../include/client.h"

#define OK_CODE 0
#define ERR_CODE 1

int main(int argc, char *argv[]) {
    Client client;
    client.run();
    return OK_CODE;
}