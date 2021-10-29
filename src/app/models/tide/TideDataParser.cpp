//
// Created by ciroque on 2021-10-21.
//
#include <utility>

#include <include/nlohmann/json.hpp>
#include "TideDataParser.h"

using json = nlohmann::json;

std::vector<TimeSeriesDataPoint> TideDataParser::Parse(const std::string& data) {
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

    return tideLevels;
}
