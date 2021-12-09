//
// Created by wagnerdev on 9/19/21.
//

#ifndef TIDAL_DAILYPREDICTION_H
#define TIDAL_DAILYPREDICTION_H


#include "src/app/models/lunar/LunarData.h"
#include "src/app/models/tide/TideData.h"
#include "src/app/models/weather/WeatherData.h"

class DailyPrediction {
private:
    tm date = {};
    LunarData lunarData;
    TideData tideData;
    WeatherData weatherData;

public:
    explicit DailyPrediction(tm date);
    DailyPrediction(tm date, LunarData lunarData, TideData tideData, WeatherData weatherData);

    inline LunarData GetLunarData() { return this->lunarData; }
    inline TideData GetTideData() { return this->tideData; }
    inline WeatherData GetWeatherData() { return this->weatherData; }
    inline tm GetDate() { return this->date; }
};

#endif //TIDAL_DAILYPREDICTION_H
