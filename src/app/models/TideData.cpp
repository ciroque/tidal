//
// Created by swagner on 10/4/20.
//

#include <iostream>
#include <include/nlohmann/json.hpp>
#include <utility>
#include "TideData.h"
#include "src/app/TimeSeriesDataPoint.h"

using json = nlohmann::json;

TideData::TideData() {
    highestTide = 0.0;
    lowestTide = 0.0;
}

TideData::TideData(std::vector<TimeSeriesDataPoint> tideLevels) {
    this->tideLevels = std::move(tideLevels);
}

// Time-series JSON; t is timestamp, v is value in feet
TideData TideData::Parse(const std::string& data) {
    json j = json::parse(data);

    std::vector<TimeSeriesDataPoint> timeSeriesDataPoints;

    for (auto & it : j) {
        for(json::iterator it2 = it.begin(); it2 != it.end(); ++it2) {
            auto entry = it2.value();
            std::string timestamp;
            std::string value;

            entry["t"].get_to(timestamp);
            entry["v"].get_to(value);

            timeSeriesDataPoints.emplace_back(timestamp, std::stof(value, nullptr));
        }
    }

    auto comparator = [](TimeSeriesDataPoint l, TimeSeriesDataPoint r) { return l.getValue() < r.getValue(); };

    auto tideData = TideData();

    tideData.tideLevels = timeSeriesDataPoints;
    tideData.lowestTide = std::min_element(timeSeriesDataPoints.begin(), timeSeriesDataPoints.end(), comparator)->getValue();
    tideData.highestTide = std::max_element(timeSeriesDataPoints.begin(), timeSeriesDataPoints.end(), comparator)->getValue();

    return tideData;
}

std::vector<TimeSeriesDataPoint> TideData::TideLevelsForDate(tm date) {
    return TimeSeriesDataPoint::ValuesForDate(this->tideLevels, date);
}
