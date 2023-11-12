//
// Created by swagner on 10/4/20.
//

#include "DisplayData.h"

#include <utility>
#include <src/app/Time.h>

DisplayData::DisplayData() : DisplayData(
        std::vector<DailyPrediction>(),
        TimeSeriesDataPoint(),
        TimeSeriesDataPoint(),
        TimeSeriesDataPoint(),
        TimeSeriesDataPoint()) { }

DisplayData::DisplayData(
    std::vector<DailyPrediction> dailyPredictions,
    TimeSeriesDataPoint highestTideLevel,
    TimeSeriesDataPoint lowestTideLevel,
    TimeSeriesDataPoint highestTemperature,
    TimeSeriesDataPoint lowestTemperature) {
    this->dailyPredictions = std::move(dailyPredictions);
    this->highestTideLevel = highestTideLevel;
    this->lowestTideLevel = lowestTideLevel;
    this->highestTemperature = highestTemperature;
    this->lowestTemperature = lowestTemperature;
    this->hour = Time::HoursNow();
}
