//
// Created by swagner on 9/26/21.
//

#include "ConfigFileNotFoundException.h"

ConfigFileNotFoundException::ConfigFileNotFoundException(const std::string& filename) {
    this->errorMessage = std::string("Configuration file was not found: ") + filename;
}
