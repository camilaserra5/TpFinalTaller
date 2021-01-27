#include "../include/cliente.h"
<<<<<<< HEAD
#include "../include/client.h"
=======

>>>>>>> d736525b05b728bc0dd858bb4c0f59e77974ade9
#define OK_CODE 0
#define ERR_CODE 1

int main(int argc, char *argv[]) {
<<<<<<< HEAD
    Cliente client(argv[1], argv[2]);
    //Client client;
=======
    Cliente client(reinterpret_cast<const char *>(1), reinterpret_cast<const char *>(2));
>>>>>>> d736525b05b728bc0dd858bb4c0f59e77974ade9
    client.run();
    return OK_CODE;
}
