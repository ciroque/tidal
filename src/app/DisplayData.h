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

class DisplayData {
public:
    bool loaded;
    unsigned int hour;
    LunarData lunarData;
    WeatherData weatherData;
    TideData tideData;
};


#endif //TIDAL_DISPLAYDATA_H
