//
// Created by swagner on 10/4/20.
//

#include <include/nlohmann/json.hpp>
#include <iostream>
#include <string>

#include "WeatherParser.h"

using json = nlohmann::json;

std::map<std::string, std::vector<TimeSeriesDataPoint>> WeatherParser::Parse(std::string data) {
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

    json j = json::parse(data);

    std::vector<std::string> listNames { "maxTemperature", "minTemperature", "temperature", "apparentTemperature" };
    std::map<std::string, std::vector<TimeSeriesDataPoint>> predictions {
            {"maxTemperature", std::vector<TimeSeriesDataPoint>()},
            {"minTemperature", std::vector<TimeSeriesDataPoint>()},
            {"temperature", std::vector<TimeSeriesDataPoint>()},
            {"apparentTemperature", std::vector<TimeSeriesDataPoint>()}
    };

    auto properties = j["properties"];

    std::string timestamp;
    double value;

    for(const auto& listName : listNames) {
        std::cout << "list name: " << listName << std::endl;
        auto items = properties[listName]["values"];

        for(auto& item : items) {

            item["validTime"].get_to(timestamp);
            item["value"].get_to(value);
            std::cout << "key(" << timestamp << "), value(" << value << ")." << std::endl;

            predictions[listName].emplace_back(timestamp, value);
        }
    }

    return predictions;
}
