//
// Created by wagnerdev on 9/19/21.
//

#ifndef TIDAL_PREDICTIONS_H
#define TIDAL_PREDICTIONS_H


#include <src/app/config/AppConfig.h>
#include <src/app/models/DisplayData.h>
#include "LunarPredictions.h"

class Predictions {
public:
    explicit Predictions(AppConfig *config);
    DisplayData BuildDisplayData();

private:
    AppConfig *config;

    LunarPredictions loadLunarData();
    TideData loadTideData();
    WeatherParser loadWeatherData();

    static TideData extractTideDataForDay(TideData tideData, tm date);
    static WeatherData extractWeatherDataForDay(WeatherParser aggregateWeatherData, tm date);

    static TimeSeriesDataPoint findHighestTideLevel(const std::vector<DailyPrediction>& dailyPredictions);
    static TimeSeriesDataPoint findLowestTideLevel(const std::vector<DailyPrediction>& dailyPredictions);

    };

#endif //TIDAL_PREDICTIONS_H
