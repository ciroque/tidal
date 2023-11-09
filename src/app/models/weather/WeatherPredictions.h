//
// Created by ciroque on 2021-10-21.
//

#ifndef TIDAL_WEATHERPREDICTIONS_H
#define TIDAL_WEATHERPREDICTIONS_H


#include <src/app/retrievers/WeatherRetriever.h>
#include <src/app/TimeSeriesDataPoint.h>
#include "WeatherData.h"
#include "RawWeatherDatum.h"

class WeatherPredictions {
private:
    WeatherRetriever retriever;
    std::map<std::string, std::vector<TimeSeriesDataPoint>> predictions;

    void UnrollEncoding(std::map<std::string, std::vector<RawWeatherDatum>> rawPredictions);
    void PadMissingValues();

public:
    explicit WeatherPredictions(const WeatherRetriever &retriever);

    WeatherData ForDate(tm date);
    WeatherPredictions Load();
};

#endif //TIDAL_WEATHERPREDICTIONS_H
