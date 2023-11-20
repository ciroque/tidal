//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_DISPLAYDATA_H
#define TIDAL_DISPLAYDATA_H


#include <lunar.h>
#include <vector>
#include "src/app/models/weather/WeatherParser.h"
#include "src/app/models/tide/TideData.h"
#include "src/app/models/lunar/LunarData.h"
#include "DailyPrediction.h"

class DisplayData {
public:
    DisplayData();
    DisplayData(
        std::vector<DailyPrediction> dailyPredictions,
        TimeSeriesDataPoint highestTideLevel,
        TimeSeriesDataPoint lowestTideLevel,
        TimeSeriesDataPoint highestTemperature,
        TimeSeriesDataPoint lowestTemperature);

    unsigned int hour;

    std::vector<DailyPrediction> dailyPredictions;
    TimeSeriesDataPoint highestTideLevel;
    TimeSeriesDataPoint lowestTideLevel;

    TimeSeriesDataPoint highestTemperature;
    TimeSeriesDataPoint lowestTemperature;
};


#endif //TIDAL_DISPLAYDATA_H
