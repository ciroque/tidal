//
// Created by Steve Wagner on 9/23/20.
//

#include <iostream>
#include "WeatherRetriever.h"

std::string WeatherRetriever::Retrieve() {
    std::cout << "WeatherRetriever::Retrieve" << std::endl;
    auto path = BuildPath();
    return this->Retriever::Retrieve(
            config->getWeatherHttpHost(),
            config->getWeatherHttpPort(),
            path);
}

WeatherRetriever::WeatherRetriever(AppConfig *config) {
    this->config = config;
}

std::string WeatherRetriever::BuildPath() {
    return config->getWeatherHttpRootPath()
        + config->getWeatherOffice() + "/"
        + config->getWeatherGridX() + ","
        + config->getWeatherGridY();
}
