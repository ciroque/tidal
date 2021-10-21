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
#include "TidePredictions.h"
#include "WeatherPredictions.h"

Predictions::Predictions(AppConfig *config) {
    this->config = config;
}

// Starting with today, create a DailyPrediction instance and then copy / move
// the data from the various data lists (LunarData, TideData, and WeatherParser)
// for that date into the DailyPrediction instance
DisplayData Predictions::BuildDisplayData() {
    auto lunarPredictions = LunarPredictions(LunarRetriever(config)).Load();
    auto tidePredictions =  TidePredictions(TideRetriever(config)).Load();
    auto weatherPredictions = WeatherPredictions(WeatherRetriever(config)).Load();
    std::vector<DailyPrediction> dailyPredictions;

    for(int i = 0; i < config->getDaysToDisplay(); i++) {
        auto today = Time::GetDay(i);
        DailyPrediction dailyPrediction(today);
        dailyPrediction.lunarData = lunarPredictions.at(i);
        dailyPrediction.tideData = tidePredictions.ForDate(today);
        dailyPrediction.weatherData = weatherPredictions.ForDate(today);
        dailyPredictions.emplace_back(dailyPrediction);
    }

    TimeSeriesDataPoint highestTideLevel = tidePredictions.HighestTide();
    TimeSeriesDataPoint lowestTideLevel = tidePredictions.LowestTide();

    return {
            dailyPredictions,
            highestTideLevel,
            lowestTideLevel};
}
