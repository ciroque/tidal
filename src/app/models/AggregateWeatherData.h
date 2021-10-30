//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_AGGREGATEWEATHERDATA_H
#define TIDAL_AGGREGATEWEATHERDATA_H


#include <src/app/TimeSeriesDataPoint.h>

class AggregateWeatherData {
private:
    std::vector<TimeSeriesDataPoint> highTemperatures;
    std::vector<TimeSeriesDataPoint> lowTemperatures;
    std::vector<TimeSeriesDataPoint> temperatures;
    std::vector<TimeSeriesDataPoint> apparentTemperatures;

public:
    AggregateWeatherData();
    explicit AggregateWeatherData(
        std::vector<TimeSeriesDataPoint> highTemperatures,
        std::vector<TimeSeriesDataPoint> lowTemperatures,
        std::vector<TimeSeriesDataPoint> temperatures,
        std::vector<TimeSeriesDataPoint> apparentTemperatures
    );

    static AggregateWeatherData Parse(std::string);
};

#endif //TIDAL_AGGREGATEWEATHERDATA_H
