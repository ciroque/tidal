//
// Created by ciroque on 2021-10-21.
//

#ifndef TIDAL_WEATHERDATA_H
#define TIDAL_WEATHERDATA_H

#include "src/app/TimeSeriesDataPoint.h"

class WeatherData {
private:
    std::vector<TimeSeriesDataPoint> temperatures;
    std::vector<TimeSeriesDataPoint> apparentTemperatures;
    std::vector<TimeSeriesDataPoint> precipitationProbabilities;
    std::vector<TimeSeriesDataPoint> windSpeeds;
    std::vector<TimeSeriesDataPoint> windGusts;
    std::vector<TimeSeriesDataPoint> skyCover;

    TimeSeriesDataPoint highTemperature;
    TimeSeriesDataPoint lowTemperature;

public:
    WeatherData();
    WeatherData(
            std::vector<TimeSeriesDataPoint> temperatures,
            std::vector<TimeSeriesDataPoint> apparentTemperatures,
            std::vector<TimeSeriesDataPoint> precipitationProbabilities,
            std::vector<TimeSeriesDataPoint> windSpeeds,
            std::vector<TimeSeriesDataPoint> windGusts,
            std::vector<TimeSeriesDataPoint> skyCover,
            TimeSeriesDataPoint highTemperature,
            TimeSeriesDataPoint lowTemperature);
};

#endif //TIDAL_WEATHERDATA_H
