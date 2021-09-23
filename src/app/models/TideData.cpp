//
// Created by swagner on 10/4/20.
//

#include <iostream>
#include <include/nlohmann/json.hpp>
#include <utility>
#include "TideData.h"
#include "src/app/TimeSeriesDataPoint.h"

using json = nlohmann::json;

TideData::TideData() : TideData(std::vector<TimeSeriesDataPoint>()) { }

TideData::TideData(std::vector<TimeSeriesDataPoint> tideLevels) :
    TideData(std::move(tideLevels), TimeSeriesDataPoint(), TimeSeriesDataPoint()) { }

TideData::TideData(std::vector<TimeSeriesDataPoint> tideLevels, TimeSeriesDataPoint highestTideLevel, TimeSeriesDataPoint lowestTideLevel) {
    this->tideLevels = std::move(tideLevels);
    this->highestTideLevel = highestTideLevel;
    this->lowestTideLevel = lowestTideLevel;
}

// Time-series JSON; t is timestamp, v is value in feet
TideData TideData::Parse(const std::string& data) {
    json j = json::parse(data);
    std::vector<TimeSeriesDataPoint> tideLevels;

    for (auto & it : j) {
        for(json::iterator it2 = it.begin(); it2 != it.end(); ++it2) {
            auto entry = it2.value();
            std::string timestamp;
            std::string value;

            entry["t"].get_to(timestamp);
            entry["v"].get_to(value);

            tideLevels.emplace_back(timestamp, std::stof(value, nullptr));
        }
    }

    return TideData(tideLevels);
}

std::vector<TimeSeriesDataPoint> TideData::TideLevelsForDate(tm date) {
    return TimeSeriesDataPoint::ValuesForDate(this->tideLevels, date);
}

