//
// Created by swagner on 10/4/20.
//

#include "TideData.h"

#include "src/app/TimeSeriesDataPoint.h"

TideData::TideData() : TideData(std::vector<TimeSeriesDataPoint>()) { }

TideData::TideData(std::vector<TimeSeriesDataPoint> tideLevels) :
    TideData(std::move(tideLevels), TimeSeriesDataPoint(), TimeSeriesDataPoint()) { }

TideData::TideData(std::vector<TimeSeriesDataPoint> tideLevels, TimeSeriesDataPoint highestTideLevel, TimeSeriesDataPoint lowestTideLevel) {
    this->tideLevels = std::move(tideLevels);
    this->highestTideLevel = highestTideLevel;
    this->lowestTideLevel = lowestTideLevel;
}
