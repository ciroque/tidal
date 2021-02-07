//
// Created by Steve Wagner on 9/23/20.
//

#ifndef TIDAL_WEATHERRETRIEVER_H
#define TIDAL_WEATHERRETRIEVER_H


#include "Retriever.h"

class WeatherRetriever : Retriever {
public:
    std::string Retrieve();

private:
    const std::string port = "443";
    const std::string host = "api.weather.gov";
    const std::string path = "/gridpoints/sew/119,76";
};


#endif //TIDAL_WEATHERRETRIEVER_H
