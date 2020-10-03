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

    const std::string host = "www.google.com";
    const std::string path = "/";

//    const std::string host = "tidesandcurrents.noaa.gov";
//    const std::string path = "/api/datagetter?date=today&product=predictions&datum=mllw&interval=hilo&format=json&units=metric&time_zone=lst_ldt&station=9447130";


//    const std::string URL = "http://tidesandcurrents.noaa.gov/api/datagetter?date=today&product=predictions&datum=mllw&interval=hilo&format=json&units=metric&time_zone=lst_ldt&station=9447130";
};


#endif //TIDAL_TIDERETRIEVER_H
