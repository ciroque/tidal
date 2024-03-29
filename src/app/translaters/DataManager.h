//
// Created by wagnerdev on 9/19/21.
//

#ifndef TIDAL_DATAMANAGER_H
#define TIDAL_DATAMANAGER_H


#include <src/app/config/AppConfig.h>
#include <src/app/models/DisplayData.h>

class DataManager {
public:
    explicit DataManager(AppConfig *config);
    DisplayData BuildDisplayData();

private:
    AppConfig *config;

    std::vector<LunarData> loadLunarData();
    TideData loadTideData();
    AggregateWeatherData loadWeatherData();

    static TideData extractTideDataForDay(TideData tideData, tm date);

    static TimeSeriesDataPoint findHighestTideLevel(const std::vector<DailyPrediction>& dailyPredictions);
    static TimeSeriesDataPoint findLowestTideLevel(const std::vector<DailyPrediction>& dailyPredictions);

    };

#endif //TIDAL_DATAMANAGER_H
