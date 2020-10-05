//
// Created by Steve Wagner on 9/23/20.
//

#include <iostream>
#include "WeatherRetriever.h"

void WeatherRetriever::Retrieve() {
    std::cout << "WeatherRetriever::Retrieve" << std::endl;
    std::string res = this->Retriever::Retrieve(host, port, path);
//    std::cout << res << std::endl;
}
