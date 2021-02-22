#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
private:
    std::thread thread;

public:
    /*
      * Creara a clase Thread dejandola valida para uso
    */
    Thread();
    /*
      * arranca el hilo e invoca a la fucion run
    */
    void start();
    /*
      * hace join del hilo
    */
    void join();
    /*
      * corre el hilo
    */
    virtual void run() = 0;
    /*
      * liberara la clase
    */
    virtual ~Thread() = 0;

    Thread(const Thread &) = delete;

    Thread &operator=(const Thread &) = delete;
    /*
      * costructor pr movimiento
    */
    Thread(Thread &&other);
    /*
      * operador = por movimeiento 
    */
    Thread &operator=(Thread &&other);
};

#endif /* THREAD_H */
