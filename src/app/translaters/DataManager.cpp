//
// Created by wagnerdev on 9/19/21.
//

#include <src/app/retrievers/WeatherRetriever.h>
#include <src/app/retrievers/TideRetriever.h>
#include <src/app/retrievers/LunarRetriever.h>
#include <src/app/models/DailyPrediction.h>
#include <src/app/Time.h>
#include "DataManager.h"

DataManager::DataManager(AppConfig *config) {
    this->config = config;
}

// Starting with today, create a DailyPrediction instance and then copy / move
// the data from the various data lists (LunarData, TideData, and WeatherData)
// for that date into the DailyPrediction instance
DisplayData DataManager::BuildDisplayData() {
    auto displayData = DisplayData();
    auto today = Time::GetDay();

    // Extract the Lunar data
    auto lunarData = loadLunarData();
    DailyPrediction dailyPrediction(today);
    dailyPrediction.lunarData = lunarData.at(0);

    // Extract the Tide data
    dailyPrediction.tideData = extractTideDataForDay(today);
    displayData.dailyPredictions.emplace_back(dailyPrediction);

    // Extract the Weather data

    // Set the top-level high and low tide values

    return displayData;
}

std::vector<LunarData> DataManager::loadLunarData() {
    LunarRetriever lunarRetriever(config);
    auto lunarData = lunarRetriever.Retrieve();
    return lunarData;
}

TideData DataManager::loadTideData() {
    TideRetriever tideRetriever(config);
    std::string tideData = tideRetriever.Retrieve();
    return TideData::Parse(tideData);
}

TideData DataManager::extractTideDataForDay(tm date) {
    auto tideData = loadTideData();
    auto tideLevelsForDay = tideData.TideLevelsForDate(date);
    return TideData(tideLevelsForDay);
}

// TODO: Implementate the parser for the Weather Data...
WeatherData DataManager::loadWeatherData() {
    WeatherRetriever weatherRetriever(config);
    std::string weatherData = weatherRetriever.Retrieve();
    return WeatherData::Parse(weatherData);
}
