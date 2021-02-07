//
// Created by Steve Wagner on 9/23/20.
//

#include <iostream>
#include <include/nlohmann/json.hpp>
#include "WeatherRetriever.h"

#include "../../include/nlohmann/json.hpp"

// for convenience
//using json = nlohmann::json;

std::string WeatherRetriever::Retrieve() {
    std::cout << "WeatherRetriever::Retrieve" << std::endl;
    return this->Retriever::Retrieve(host, port, path);
}
