//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_DISPLAYDATA_H
#define TIDAL_DISPLAYDATA_H


#include <lunar.h>
#include <vector>
#include "WeatherData.h"
#include "TideData.h"
#include "LunarData.h"
#include "DailyPrediction.h"

class DisplayData {
public:
    bool loaded = false;
    unsigned int hour;

    // OLD AND BUSTED
    LunarData lunarData;
    WeatherData weatherData;
    TideData tideData;

    // THE NEW HOTNESS
    std::vector<DailyPrediction> dailyPredictions;
};


#endif //TIDAL_DISPLAYDATA_H
