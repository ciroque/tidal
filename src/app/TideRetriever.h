//
// Created by Steve Wagner on 9/23/20.
//

#ifndef TIDAL_TIDERETRIEVER_H
#define TIDAL_TIDERETRIEVER_H

#include "Retriever.h"

class TideRetriever : Retriever {
public:
    void Retrieve();

private:
    const std::string port = "443";
    const std::string host = "api.tidesandcurrents.noaa.gov";
    const std::string path = "/mdapi/prod/webapi/stations/9447130.json";
};


#endif //TIDAL_TIDERETRIEVER_H
