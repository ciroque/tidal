//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_TIDEDATA_H
#define TIDAL_TIDEDATA_H


#include <string>
#include "src/app/TimeSeriesDataPoint.h"

class TideData {
private:
    std::vector<TimeSeriesDataPoint> tideLevels;
    TimeSeriesDataPoint highestTideLevel;
    TimeSeriesDataPoint lowestTideLevel;

public:
    TideData();
    explicit TideData(std::vector<TimeSeriesDataPoint> tideLevels);
    TideData(std::vector<TimeSeriesDataPoint> tideLevels, TimeSeriesDataPoint highestTideLevel, TimeSeriesDataPoint lowestTideLevel);

    inline TimeSeriesDataPoint getHighestTideLevel() { return this->highestTideLevel; }
    inline TimeSeriesDataPoint getLowestTideLevel() { return this->lowestTideLevel; }
    inline std::vector<TimeSeriesDataPoint> getTideLevels() { return this->tideLevels; }
};


#endif //TIDAL_TIDEDATA_H
