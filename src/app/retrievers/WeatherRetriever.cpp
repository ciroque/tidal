//
// Created by Steve Wagner on 9/23/20.
//

#include <iostream>
#include "WeatherRetriever.h"

std::string WeatherRetriever::Retrieve() {
    std::cout << "WeatherRetriever::Retrieve" << std::endl;
    return this->Retriever::Retrieve(
            config->getWeatherHttpHost(),
            config->getWeatherHttpPort(),
            BuildPath());
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
