//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_WEATHERPARSER_H
#define TIDAL_WEATHERPARSER_H

#include <map>

#include <src/app/TimeSeriesDataPoint.h>
#include "RawWeatherDatum.h"

class WeatherParser {
public:
    static std::map<std::string, std::vector<RawWeatherDatum>> Parse(const std::string&);
};

#endif //TIDAL_WEATHERPARSER_H
