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
    static TideData Parse(const std::string&);
    std::vector<TimeSeriesDataPoint> TideLevelsForDate(tm date);
};


#endif //TIDAL_TIDEDATA_H
