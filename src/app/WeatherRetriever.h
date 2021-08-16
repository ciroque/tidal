//
// Created by Steve Wagner on 9/23/20.
//

#ifndef TIDAL_WEATHERRETRIEVER_H
#define TIDAL_WEATHERRETRIEVER_H


#include <src/app/config/AppConfig.h>
#include "Retriever.h"

class WeatherRetriever : Retriever {
public:
    explicit WeatherRetriever(AppConfig *pConfig);

    std::string Retrieve();

private:
    AppConfig *config;
    std::string BuildPath();
};


#endif //TIDAL_WEATHERRETRIEVER_H
