//
// Created by ciroque on 2021-10-21.
//

#include "WeatherPredictions.h"
#include "WeatherParser.h"

WeatherPredictions::WeatherPredictions(const WeatherRetriever &retriever) : retriever(retriever) { }

WeatherPredictions WeatherPredictions::Load() {
    auto data = retriever.Retrieve();
    this->predictions = WeatherParser::Parse(data);
    return *this;
}

WeatherData WeatherPredictions::ForDate(const tm date) {
    auto temperatures = TimeSeriesDataPoint::ValuesForDate(this->predictions["temperature"], date);
    auto apparentTemperatures = TimeSeriesDataPoint::ValuesForDate(this->predictions["apparentTemperature"], date);
    auto highTemperature = TimeSeriesDataPoint::ValuesForDate(this->predictions["maxTemperature"], date);
    auto lowTemperature = TimeSeriesDataPoint::ValuesForDate(this->predictions["minTemperature"], date);
    return {};
}
