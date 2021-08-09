//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_TIDEDATA_H
#define TIDAL_TIDEDATA_H


#include <string>
#include "TimeSeriesDataPoint.h"

class TideData {
private:
    std::vector<TimeSeriesDataPoint> tideLevels;
    float highestTide;
    float lowestTide;

public:
    static TideData Parse(const std::string&);

};


#endif //TIDAL_TIDEDATA_H
