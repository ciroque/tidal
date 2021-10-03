//
// Created by swagner on 10/4/20.
//

#include "DisplayData.h"

#include <utility>
#include <src/app/Time.h>

DisplayData::DisplayData() : DisplayData(
std::vector<DailyPrediction>(),
TimeSeriesDataPoint(),
TimeSeriesDataPoint()) { }

DisplayData::DisplayData(std::vector<DailyPrediction> dailyPredictions, TimeSeriesDataPoint highestTideLevel,
                         TimeSeriesDataPoint lowestTideLevel) {
    this->dailyPredictions = std::move(dailyPredictions);
    this->highestTideLevel = highestTideLevel;
    this->lowestTideLevel = lowestTideLevel;
    this->hour = Time::HoursNow();
}
