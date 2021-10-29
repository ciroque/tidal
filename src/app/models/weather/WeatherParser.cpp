//
// Created by swagner on 10/4/20.
//

#include <include/nlohmann/json.hpp>
#include <iostream>
#include <string>

#include "WeatherParser.h"
#include "RawWeatherDatum.h"

using json = nlohmann::json;

std::map<std::string, std::vector<RawWeatherDatum>> WeatherParser::Parse(const std::string& data) {
    // root.properties.maxTemperature                   Daily highs
    // root.properties.minTemperature                   Daily lows
    // root.properties.temperature                      Hourly temperatures
    // root.properties.apparentTemperature              Hourly "Feels Like"
    // ++ root.properties.windDirection                 Three-hour periods
    // ++ root.properties.windSpeed                     Three-hour periods
    // ++ root.properties.windGust                      Three-hour periods
    // +++ root.properties.probabilityOfPrecipitation   Period uses back-off algorithm
    // ++++ root.properties.snowfallAmount
    // ++ root.properties.relativeHumidity

    std::cout << data << std::endl;
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
            std::cout << "(" << item << ") " << rawWeatherDatum.GetValue() << " is valid for " << rawWeatherDatum.GetRecurrence() << " hours." << std::endl;

            predictions[listName].emplace_back(rawWeatherDatum);
        }
    }

    return predictions;
}
