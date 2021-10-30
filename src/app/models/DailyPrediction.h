//
// Created by wagnerdev on 9/19/21.
//

#ifndef TIDAL_DAILYPREDICTION_H
#define TIDAL_DAILYPREDICTION_H


#include "LunarData.h"
#include "TideData.h"
#include "AggregateWeatherData.h"

class DailyPrediction {
public:
    explicit DailyPrediction(tm date);

    tm date = {};
    LunarData lunarData;
    TideData tideData;
    AggregateWeatherData weatherData;
};

#endif //TIDAL_DAILYPREDICTION_H
