//            // "2021-10-21T18:00:00+00:00/PT1H"

// Created by ciroque on 2021-10-21.
//

#include "WeatherPredictions.h"
#include "WeatherParser.h"
#include "RunLengthEncoding.h"

WeatherPredictions::WeatherPredictions(const WeatherRetriever &retriever) : retriever(retriever) { }

WeatherPredictions WeatherPredictions::Load() {
    auto data = retriever.Retrieve();
    auto rawPredictions = WeatherParser::Parse(data);
    UnrollEncoding(rawPredictions);
    // TODO: Adjust Time Zone
    // TODO: Convert to std::vector<TimeSeriesDataPoint>
    // this->predictions = ...
    return *this;
}

WeatherData WeatherPredictions::ForDate(const tm date) {
//    auto temperatures = TimeSeriesDataPoint::ValuesForDate(this->predictions["temperature"], date);
//    auto apparentTemperatures = TimeSeriesDataPoint::ValuesForDate(this->predictions["apparentTemperature"], date);
//    auto highTemperature = TimeSeriesDataPoint::ValuesForDate(this->predictions["maxTemperature"], date).front();
//    auto lowTemperature = TimeSeriesDataPoint::ValuesForDate(this->predictions["minTemperature"], date).front();
//    return {
//        temperatures,
//        apparentTemperatures,
//        highTemperature,
//        lowTemperature};
    return {};
}

void WeatherPredictions::UnrollEncoding(std::map<std::string, std::vector<RawWeatherDatum>> rawPredictions) {
    std::vector<std::string> listNames {"temperature", "apparentTemperature"};
    for(const auto& listName : listNames) {
        auto items = rawPredictions[listName];
        auto unrolled = RunLengthEncoding::Decode(items);
        items.clear();
        rawPredictions[listName] = unrolled;
    }
}
