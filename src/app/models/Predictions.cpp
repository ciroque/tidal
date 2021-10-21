//
// Created by wagnerdev on 9/19/21.
//

#include <src/app/retrievers/WeatherRetriever.h>
#include <src/app/retrievers/TideRetriever.h>
#include <src/app/retrievers/LunarRetriever.h>
#include <src/app/models/DailyPrediction.h>
#include <src/app/Time.h>
#include "Predictions.h"
#include "LunarPredictions.h"

Predictions::Predictions(AppConfig *config) {
    this->config = config;
}

// Starting with today, create a DailyPrediction instance and then copy / move
// the data from the various data lists (LunarData, TideData, and WeatherParser)
// for that date into the DailyPrediction instance
DisplayData Predictions::BuildDisplayData() {
    auto lunarData = LunarPredictions(LunarRetriever(config)).Load();
    auto tideData = loadTideData();
    auto weatherData = loadWeatherData();
    std::vector<DailyPrediction> dailyPredictions;

    for(int i = 0; i < config->getDaysToDisplay(); i++) {
        auto today = Time::GetDay(i);

        // Extract the Lunar data
        DailyPrediction dailyPrediction(today);
        dailyPrediction.lunarData = lunarData.at(i);

        // Extract the Tide data
        dailyPrediction.tideData = extractTideDataForDay(tideData, today);

        // Extract the Weather data
        dailyPrediction.weatherData = extractWeatherDataForDay(weatherData, today);

        dailyPredictions.emplace_back(dailyPrediction);
    }

    TimeSeriesDataPoint highestTideLevel = findHighestTideLevel(dailyPredictions);
    TimeSeriesDataPoint lowestTideLevel = findLowestTideLevel(dailyPredictions);

    return {
            dailyPredictions,
            highestTideLevel,
            lowestTideLevel};
}

//LunarPredictions Predictions::loadLunarData() {
//    LunarRetriever lunarRetriever(config);
//    auto lunarData = lunarRetriever.Retrieve();
//    return LunarPredictions(lunarData, <#initializer#>);
//}

TideData Predictions::loadTideData() {
    TideRetriever tideRetriever(config);
    std::string tideData = tideRetriever.Retrieve();
    return TideData::Parse(tideData);
}

TideData Predictions::extractTideDataForDay(TideData tideData, tm date) {
    auto tideLevelsForDay = tideData.TideLevelsForDate(date);
    TimeSeriesDataPoint highestTideLevel = TimeSeriesDataPoint::MaxValue(tideLevelsForDay);
    TimeSeriesDataPoint lowestTideLevel = TimeSeriesDataPoint::MinValue(tideLevelsForDay);
    return {tideLevelsForDay, highestTideLevel, lowestTideLevel};
}

WeatherData Predictions::extractWeatherDataForDay(WeatherParser aggregateWeatherData, tm date) {
    return {};
}

// TODO: Implementate the parser for the Weather Data...
WeatherParser Predictions::loadWeatherData() {
    WeatherRetriever weatherRetriever(config);
    std::string weatherData = weatherRetriever.Retrieve();

    // TODO: The result from WeatherParser::Parse(weatherData) will need to be translated into

    return WeatherParser();
}

TimeSeriesDataPoint Predictions::findHighestTideLevel(const std::vector<DailyPrediction>& dailyPredictions) {
    std::vector<TimeSeriesDataPoint> highestLevels;
    highestLevels.reserve(dailyPredictions.size());

    for(auto dailyPrediction : dailyPredictions) {
        highestLevels.emplace_back(dailyPrediction.tideData.getHighestTideLevel());
    }
    return TimeSeriesDataPoint::MaxValue(highestLevels);
}

TimeSeriesDataPoint Predictions::findLowestTideLevel(const std::vector<DailyPrediction>& dailyPredictions) {
    std::vector<TimeSeriesDataPoint> lowestLevels;
    lowestLevels.reserve(dailyPredictions.size());

    for(auto dailyPrediction : dailyPredictions) {
        lowestLevels.emplace_back(dailyPrediction.tideData.getLowestTideLevel());
    }
    return TimeSeriesDataPoint::MinValue(lowestLevels);
}
