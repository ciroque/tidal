//            // "2021-10-21T18:00:00+00:00/PT1H"

// Created by ciroque on 2021-10-21.
//

#include "WeatherPredictions.h"
#include "WeatherParser.h"

WeatherPredictions::WeatherPredictions(const WeatherRetriever &retriever) : retriever(retriever) { }

WeatherPredictions WeatherPredictions::Load() {
    auto data = retriever.Retrieve();
    this->rawPredictions = WeatherParser::Parse(data);
    // TODO: Unroll Run Length Encoded values
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
