//
// Created by wagnerdev on 10/3/21.
//

#include "FrameBufferOpenException.h"

FrameBufferOpenException::FrameBufferOpenException(const std::string &name) {
    this->errorMessage = std::string("Failed to open frame buffer : ") + name;
}
