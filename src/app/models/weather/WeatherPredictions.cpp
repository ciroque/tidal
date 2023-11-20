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
    PadMissingValues();

    return *this;
}

WeatherData WeatherPredictions::ForDate(const tm date) {
    auto temperatures = TimeSeries::ValuesForDate(this->predictions["temperature"], date);
    auto apparentTemperatures = TimeSeries::ValuesForDate(this->predictions["apparentTemperature"], date);

    auto precipitationProbabilities = TimeSeries::ValuesForDate(this->predictions["probabilityOfPrecipitation"], date);
    auto windSpeeds = TimeSeries::ValuesForDate(this->predictions["windSpeed"], date);
    auto windGusts = TimeSeries::ValuesForDate(this->predictions["windGust"], date);
    auto skyCover = TimeSeries::ValuesForDate(this->predictions["skyCover"], date);

    auto highTemperature = TimeSeries::ValuesForDate(this->predictions["temperature"], date).front();
    auto lowTemperature = TimeSeries::ValuesForDate(this->predictions["temperature"], date).front();
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

TimeSeriesDataPoint WeatherPredictions::HighestTemperature() {
    return TimeSeries::MaxValue(this->predictions["temperature"]);
}

TimeSeriesDataPoint WeatherPredictions::LowestTemperature() {
    return TimeSeries::MinValue(this->predictions["temperature"]);
}

// The use of std::vector::insert here is reasonably inefficient, but shouldn't be a problem. Sometime in the future
// if someone is bored go ahead and fix it. Possibly just spin up a new vector and copy the values over...?
void WeatherPredictions::PadMissingValues() {
    for( const auto& listName : WeatherCommon::PredictionKeys) {
        auto items = this->predictions[listName];
        auto head = items.front();
        auto missing = head.getTimestamp().tm_hour - 1;
        for(missing; missing >= 0; missing--) {
            auto padTimestamp = head.getTimestamp();
            padTimestamp.tm_hour = missing;
            TimeSeriesDataPoint pad = TimeSeriesDataPoint(padTimestamp, head.getValue());
            items.insert(items.begin(), pad);
        }
        this->predictions[listName].clear();
        this->predictions[listName] = items;
    }
}
