//
// Created by ciroque on 2021-10-21.
//

#include "WeatherData.h"


WeatherData::WeatherData() :
    WeatherData(std::vector<TimeSeriesDataPoint>(),
                std::vector<TimeSeriesDataPoint>(),
                std::vector<TimeSeriesDataPoint>(),
                std::vector<TimeSeriesDataPoint>(),
                std::vector<TimeSeriesDataPoint>(),
                std::vector<TimeSeriesDataPoint>(),
                TimeSeriesDataPoint(),
                TimeSeriesDataPoint()) { }

    WeatherData::WeatherData(std::vector<TimeSeriesDataPoint> temperatures,
                         std::vector<TimeSeriesDataPoint> apparentTemperatures,
                         std::vector <TimeSeriesDataPoint> precipitationProbabilities,
                        std::vector <TimeSeriesDataPoint> windSpeeds,
                        std::vector <TimeSeriesDataPoint> windGusts,
                        std::vector <TimeSeriesDataPoint> skyCover,
                         TimeSeriesDataPoint highTemperature,
                         TimeSeriesDataPoint lowTemperature) {
    this->temperatures = std::move(temperatures);
    this->apparentTemperatures = std::move(apparentTemperatures);
    this->highTemperature = highTemperature;
    this->lowTemperature = lowTemperature;
    this->precipitationProbabilities = std::move(precipitationProbabilities);
    this->windSpeeds = std::move(windSpeeds);
    this->windGusts = std::move(windGusts);
    this->skyCover = std::move(skyCover);
}
