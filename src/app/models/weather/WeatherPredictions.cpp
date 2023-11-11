//            // "2021-10-21T18:00:00+00:00/PT1H"

// Created by ciroque on 2021-10-21.
//

#include "WeatherCommon.h"
#include "WeatherPredictions.h"
#include "WeatherParser.h"
#include "RunLengthEncoding.h"
#include "src/app/models/utils/TimeSeries.h"

WeatherPredictions::WeatherPredictions(const WeatherRetriever &retriever) : retriever(retriever) { }

WeatherPredictions WeatherPredictions::Load() {
    auto data = retriever.Retrieve();
    auto rawPredictions = WeatherParser::Parse(data);
    UnrollEncoding(rawPredictions);

    return *this;
}

WeatherData WeatherPredictions::ForDate(const tm date) {
    auto temperatures = TimeSeries::ValuesForDate(this->predictions["temperature"], date);
    auto apparentTemperatures = TimeSeries::ValuesForDate(this->predictions["apparentTemperature"], date);

    auto precipitationProbabilities = TimeSeries::ValuesForDate(this->predictions["probabilityOfPrecipitation"], date);
    auto windSpeeds = TimeSeries::ValuesForDate(this->predictions["windSpeed"], date);
    auto windGusts = TimeSeries::ValuesForDate(this->predictions["windGust"], date);
    auto skyCover = TimeSeries::ValuesForDate(this->predictions["skyCover"], date);

    auto highTemperature = TimeSeries::ValuesForDate(this->predictions["maxTemperature"], date).front();
    auto lowTemperature = TimeSeries::ValuesForDate(this->predictions["minTemperature"], date).front();
    return {
        temperatures,
        apparentTemperatures,
        precipitationProbabilities,
        windSpeeds,
        windGusts,
        skyCover,
        highTemperature,
        lowTemperature};
}

void WeatherPredictions::UnrollEncoding(std::map<std::string, std::vector<RawWeatherDatum>> rawPredictions) {
    for(const auto& listName : WeatherCommon::PredictionKeys) {
        auto items = rawPredictions[listName];
        auto unrolled = RunLengthEncoding::Decode(items);
        items.clear();
        this->predictions[listName] = unrolled;
    }
}
