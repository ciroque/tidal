//
// Created by Steve Wagner on 9/23/20.
//
// See: https://api.tidesandcurrents.noaa.gov/api/prod/
// Example: https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?
// begin_date=20201019
// &end_date=20201026
// &product=predictions
// &datum=mllw
// &interval=h
// &format=json
// &units=english
// &time_zone=lst_ldt
// &station=9447130
//
// TODO: Replace dates

#ifndef TIDAL_TIDERETRIEVER_H
#define TIDAL_TIDERETRIEVER_H

#include "Retriever.h"

class TideRetriever : Retriever {
public:
    void Retrieve();

private:
    const std::string port = "443";
    const std::string host = "api.tidesandcurrents.noaa.gov";
    const std::string rootPath = "/api/prod/datagetter?product=predictions&datum=mllw&interval=h&format=json&units=english&time_zone=lst_ldt&station=9447130&";

    std::string BuildPath();
};


#endif //TIDAL_TIDERETRIEVER_H
