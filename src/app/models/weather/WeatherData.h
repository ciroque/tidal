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

    inline std::vector<TimeSeriesDataPoint> getTemperatures() { return this->temperatures; }
    inline std::vector<TimeSeriesDataPoint> getApparentTemperatures() { return this->apparentTemperatures; }
    inline std::vector<TimeSeriesDataPoint> getPrecipitationProbabilities() { return this->precipitationProbabilities; }
    inline std::vector<TimeSeriesDataPoint> getWindSpeeds() { return this->windSpeeds; }
    inline std::vector<TimeSeriesDataPoint> getWindGusts() { return this->windGusts; }
    inline std::vector<TimeSeriesDataPoint> getSkyCover() { return this->skyCover; }
    inline TimeSeriesDataPoint getHighTemperature() { return this->highTemperature; }
    inline TimeSeriesDataPoint getLowTemperature() { return this->lowTemperature; }
};

#endif //TIDAL_WEATHERDATA_H
