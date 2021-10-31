//
// Created by swagner on 10/4/20.
//

#include <include/nlohmann/json.hpp>
#include <string>

#include "WeatherParser.h"
#include "RawWeatherDatum.h"

using json = nlohmann::json;

std::map<std::string, std::vector<RawWeatherDatum>> WeatherParser::Parse(const std::string& data) {
    json j = json::parse(data);

    std::map<std::string, std::vector<RawWeatherDatum>> predictions {
            {"maxTemperature", std::vector<RawWeatherDatum>()},
            {"minTemperature", std::vector<RawWeatherDatum>()},
            {"temperature", std::vector<RawWeatherDatum>()},
            {"apparentTemperature", std::vector<RawWeatherDatum>()}
    };

    auto properties = j["properties"];

    std::string timestamp;
    double value;

    for(auto it = predictions.begin(); it != predictions.end(); ++it) {
        auto listName = it->first;
        auto items = properties[listName]["values"];

        for(auto& item : items) {
            item["validTime"].get_to(timestamp);
            item["value"].get_to(value);

            RawWeatherDatum rawWeatherDatum = RawWeatherDatum::Build(timestamp, value);
            predictions[listName].emplace_back(rawWeatherDatum);
        }
    }

    return predictions;
}
