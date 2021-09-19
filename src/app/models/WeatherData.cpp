//
// Created by swagner on 10/4/20.
//

#include <string>
#include <iostream>
#include "WeatherData.h"

WeatherData WeatherData::Parse(std::string data) {
    // root.properties.maxTemperature                   Daily highs
    // root.properties.minTemperature                   Daily lows
    // root.properties.temperature                      Hourly temperatures
    // root.properties.apparentTemperature              Hourly "Feels Like"
    // ++ root.properties.windDirection                 Three-hour periods
    // ++ root.properties.windSpeed                     Three-hour periods
    // ++ root.properties.windGust                      Three-hour periods
    // +++ root.properties.probabilityOfPrecipitation   Period uses back-off algorithm
    // ++++ root.properties.snowfallAmount
    // ++ root.properties.relativeHumidity

    return WeatherData();
}
