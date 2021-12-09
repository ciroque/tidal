//
// Created by wagnerdev on 9/19/21.
//

#include "DailyPrediction.h"

#include <utility>

DailyPrediction::DailyPrediction(tm date) {
    this->date = date;
}

DailyPrediction::DailyPrediction(tm date, LunarData lunarData, TideData tideData, WeatherData weatherData)
    : DailyPrediction(date) {

    this->lunarData = lunarData;
    this->tideData = std::move(tideData);
    this->weatherData = std::move(weatherData);
}
