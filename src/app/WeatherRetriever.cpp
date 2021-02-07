//
// Created by Steve Wagner on 9/23/20.
//

#include <iostream>
#include "WeatherRetriever.h"

std::string WeatherRetriever::Retrieve() {
    std::cout << "WeatherRetriever::Retrieve" << std::endl;
    return this->Retriever::Retrieve(host, port, path);
}
