//
// Created by ciroque on 2021-10-21.
//

#ifndef TIDAL_TIDEDATAPARSER_H
#define TIDAL_TIDEDATAPARSER_H


#include <src/app/TimeSeriesDataPoint.h>

class TideDataParser {
public:
    static std::vector<TimeSeriesDataPoint> Parse(const std::string& data);
};


#endif //TIDAL_TIDEDATAPARSER_H
