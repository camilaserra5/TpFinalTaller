#include "thread.h"
#include <utility>

Thread::Thread() {}

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    if (thread.joinable())
        thread.join();
}

Thread::Thread(Thread &&other) {
    this->thread = std::move(other.thread);
}

Thread &Thread::operator=(Thread &&other) {
    if (this == &other) {
        return *this;
    }
    this->thread = std::move(other.thread);
    return *this;
}

Thread::~Thread() {}
