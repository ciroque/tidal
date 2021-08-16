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

#ifndef TIDAL_TIDERETRIEVER_H
#define TIDAL_TIDERETRIEVER_H

#include <src/app/config/AppConfig.h>
#include "Retriever.h"

class TideRetriever : Retriever {
public:
    explicit TideRetriever(AppConfig *config);
    std::string Retrieve();

private:
    AppConfig *config;

    std::string BuildPath();
};

#endif //TIDAL_TIDERETRIEVER_H
