//
// Created by swagner on 9/26/21.
//

#ifndef TIDAL_CONFIGFILENOTFOUNDEXCEPTION_H
#define TIDAL_CONFIGFILENOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

class ConfigFileNotFoundException : public std::exception {
private:
    std::string errorMessage;

public:
    explicit ConfigFileNotFoundException(const std::string& filename);

    [[nodiscard]] const char * what() const noexcept override {
        return this->errorMessage.c_str();
    }
};

#endif //TIDAL_CONFIGFILENOTFOUNDEXCEPTION_H
