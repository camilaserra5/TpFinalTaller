
#include <errno.h>
#include <iostream>
#include <string>
#include "../include/InvalidMapException.h"

InvalidMapException::InvalidMapException(const std::string &error) noexcept {
    this->mensaje_error = error;
}

const char *InvalidMapException::what() const noexcept {
    return this->mensaje_error.c_str();
}

InvalidMapException::~InvalidMapException() {}
