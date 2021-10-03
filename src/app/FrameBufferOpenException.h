//
// Created by wagnerdev on 10/3/21.
//

#ifndef TIDAL_FRAMEBUFFEROPENEXCEPTION_H
#define TIDAL_FRAMEBUFFEROPENEXCEPTION_H

#include <exception>
#include <string>

class FrameBufferOpenException : public std::exception {
private:
    std::string errorMessage;

public:
    explicit FrameBufferOpenException(const std::string& name);

    [[nodiscard]] const char * what() const noexcept override {
        return this->errorMessage.c_str();
    }
};


#endif //TIDAL_FRAMEBUFFEROPENEXCEPTION_H
