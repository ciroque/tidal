//
// Created by ciroque on 2021-10-21.
//

#include "WeatherData.h"


WeatherData::WeatherData() :
    WeatherData(std::vector<TimeSeriesDataPoint>(), std::vector<TimeSeriesDataPoint>(), TimeSeriesDataPoint(), TimeSeriesDataPoint()) { }

WeatherData::WeatherData(std::vector<TimeSeriesDataPoint> temperatures,
                         std::vector<TimeSeriesDataPoint> apparentTemperatures, TimeSeriesDataPoint highTemperature,
                         TimeSeriesDataPoint lowTemperature) {
    this->temperatures = std::move(temperatures);
    this->apparentTemperatures = std::move(apparentTemperatures);
    this->highTemperature = highTemperature;
    this->lowTemperature = lowTemperature;
}
