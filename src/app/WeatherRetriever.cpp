//
// Created by Steve Wagner on 9/23/20.
//

#include <iostream>
#include <include/nlohmann/json.hpp>
#include "WeatherRetriever.h"

#include "../../include/nlohmann/json.hpp"

// for convenience
using json = nlohmann::json;

void WeatherRetriever::Retrieve() {
    std::cout << "WeatherRetriever::Retrieve" << std::endl;
    std::string res = this->Retriever::Retrieve(host, port, path);
    auto j = json::parse(res);
    std::cout << j.dump(2) << std::endl;
}
