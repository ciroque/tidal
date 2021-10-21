//
// Created by wagnerdev on 9/19/21.
//

#ifndef TIDAL_DAILYPREDICTION_H
#define TIDAL_DAILYPREDICTION_H


#include "LunarData.h"
#include "TideData.h"
#include "WeatherData.h"

class DailyPrediction {

    // TODO: Proper encapsulation
public:
    explicit DailyPrediction(tm date);

    tm date = {};
    LunarData lunarData;
    TideData tideData;
    WeatherData weatherData;
};

#endif //TIDAL_DAILYPREDICTION_H
