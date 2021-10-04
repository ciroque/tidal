//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_DISPLAYDATA_H
#define TIDAL_DISPLAYDATA_H


#include <lunar.h>
#include <vector>
#include "AggregateWeatherData.h"
#include "TideData.h"
#include "LunarData.h"
#include "DailyPrediction.h"

class DisplayData {
public:
    DisplayData();
    DisplayData(std::vector<DailyPrediction> dailyPredictions, TimeSeriesDataPoint highestTideLevel,
                TimeSeriesDataPoint lowestTideLevel);

    unsigned int hour;

    std::vector<DailyPrediction> dailyPredictions;
    TimeSeriesDataPoint highestTideLevel;
    TimeSeriesDataPoint lowestTideLevel;
};


#endif //TIDAL_DISPLAYDATA_H
