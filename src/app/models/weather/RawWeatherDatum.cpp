//
// Created by ciroque on 2021-10-21.
//

#include "RawWeatherDatum.h"

#include <string>

std::regex ISO8601_DURATION_HOUR_EXTRACT = std::regex("^/?PT([0-9]+)H$");

RawWeatherDatum::RawWeatherDatum(tm timestamp, int recurrence, double value) {
    this->timestamp = timestamp;
    this->recurrence = recurrence;
    this->value = value;
}

int RawWeatherDatum::Recurrence(const std::string& validTime) {
    int hours = 1;
    auto index = validTime.find(DURATION_DELIMITER);

    if(index != std::string::npos) {
        auto duration = validTime.substr(index);
        std::smatch matches;
        if(std::regex_search(duration, matches, ISO8601_DURATION_HOUR_EXTRACT)) {
            hours = std::stoi(matches[1].str());
        }
    }

    return hours;
}

RawWeatherDatum RawWeatherDatum::Build(const std::string& validTime, double value) {
    int recurrence = RawWeatherDatum::Recurrence(validTime);
    tm timestamp{};
    strptime(validTime.c_str(), "%Y-%m-%dT%H:%M", &timestamp);

    return {
        timestamp,
        recurrence,
        value
    };
}
