//
// Created by swagner on 10/4/20.
//

#include <include/nlohmann/json.hpp>
#include <string>
#include <utility>

#include "AggregateWeatherData.h"

#include <iostream>
#include <fstream>

using json = nlohmann::json;

AggregateWeatherData AggregateWeatherData::Parse(std::string data) {
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
//            for(json::iterator it2 = item.begin(); it2 != item.end(); ++it2) {
//                auto entry = it2.value();
//                std::cout << "--> " << entry.dump() << " <--" << std::endl;
//            }
        }
    }

    return {};
}

AggregateWeatherData::AggregateWeatherData() :
    AggregateWeatherData(
        std::vector<TimeSeriesDataPoint>(),
        std::vector<TimeSeriesDataPoint>(),
        std::vector<TimeSeriesDataPoint>(),
        std::vector<TimeSeriesDataPoint>()) { }

AggregateWeatherData::AggregateWeatherData(
    std::vector<TimeSeriesDataPoint> highTemperatures,
    std::vector<TimeSeriesDataPoint> lowTemperatures,
    std::vector<TimeSeriesDataPoint> temperatures,
    std::vector<TimeSeriesDataPoint> apparentTemperatures)
{
    this->highTemperatures = std::move(highTemperatures);
    this->lowTemperatures = std::move(lowTemperatures);
    this->temperatures = std::move(temperatures);
    this->apparentTemperatures = std::move(apparentTemperatures);
}
