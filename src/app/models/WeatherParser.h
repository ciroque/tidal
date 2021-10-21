//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_WEATHERPARSER_H
#define TIDAL_WEATHERPARSER_H

#include <map>

#include <src/app/TimeSeriesDataPoint.h>

class WeatherParser {
public:
    static std::map<std::string, std::vector<TimeSeriesDataPoint>> Parse(std::string);
};

#endif //TIDAL_WEATHERPARSER_H
