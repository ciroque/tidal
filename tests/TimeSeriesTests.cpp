//
// Created by ciroque on 2021-10-31.
//
#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include "../src/app/TimeSeriesDataPoint.h"
#include "../src/app/models/utils/TimeSeries.h"
#include "../src/app/models/weather/RawWeatherDatum.h"

TEST_CASE("TimeSeries") {
    SECTION("ValuesForHour") {
        SECTION("With TimeSeriesDataPoints") {
            auto timeSeriesData = std::vector<TimeSeriesDataPoint> {
                    {tm{.tm_hour = 3}, 0.0},
                    {tm{.tm_hour = 2}, 0.0},
                    {tm{.tm_hour = 3}, 0.0},
                    {tm{.tm_hour = 3}, 0.0},
                    {tm{.tm_hour = 0}, 0.0}
            };

            REQUIRE(TimeSeries::ValuesForHour<TimeSeriesDataPoint>(timeSeriesData, 3).size() == 3);
        }

        SECTION("With RawWeatherData") {
            auto rawWeatherData = std::vector<RawWeatherDatum> {
                    {tm{.tm_hour = 3}, 1, 1.0},
                    {tm{.tm_hour = 3}, 3, 2.0},
                    {tm{.tm_hour = 2}, 1, 3.0},
                    {tm{.tm_hour = 3}, 1, 4.0},
                    {tm{.tm_hour = 5}, 1, 5.0}
            };

            REQUIRE(TimeSeries::ValuesForHour<RawWeatherDatum>(rawWeatherData, 3).size() == 3);
            REQUIRE(TimeSeries::ValuesForHour<RawWeatherDatum>(rawWeatherData, 3).at(1).GetRecurrence() == 3);
        }
    }

    SECTION("ValuesForDate") {
        auto date = tm{.tm_mday = 3};
        SECTION("With TimeSeriesDataPoints") {
            auto timeSeriesData = std::vector<TimeSeriesDataPoint> {
                    {tm{.tm_mday = 3}, 0.0},
                    {tm{.tm_mday = 2}, 0.0},
                    {tm{.tm_mday =
                    3}, 0.0},
                    {tm{.tm_mday = 3}, 0.0},
                    {tm{.tm_mday = 0}, 0.0}
            };

            REQUIRE(TimeSeries::ValuesForDate<TimeSeriesDataPoint>(timeSeriesData, date).size() == 3);
        }

        SECTION("With RawWeatherData") {
            auto rawWeatherData = std::vector<RawWeatherDatum> {
                    {tm{.tm_mday = 3}, 1, 1.0},
                    {tm{.tm_mday = 3}, 3, 2.0},
                    {tm{.tm_mday = 2}, 1, 3.0},
                    {tm{.tm_mday = 3}, 1, 4.0},
                    {tm{.tm_mday = 5}, 1, 5.0}
            };

            REQUIRE(TimeSeries::ValuesForDate<RawWeatherDatum>(rawWeatherData, date).size() == 3);
            REQUIRE(TimeSeries::ValuesForDate<RawWeatherDatum>(rawWeatherData, date).at(1).GetRecurrence() == 3);
        }
    }

    SECTION("MinValue") {
        SECTION("With TimeSeriesDataPoints") {
            auto timeSeriesData = std::vector<TimeSeriesDataPoint> {
                    {tm{.tm_mday = 3}, 100.0},
                    {tm{.tm_mday = 2}, 10.0},
                    {tm{.tm_mday = 3}, 30.0},
                    {tm{.tm_mday = 3}, 5.0},
                    {tm{.tm_mday = 0}, 5.1}
            };

            REQUIRE(TimeSeries::MinValue<TimeSeriesDataPoint>(timeSeriesData).getValue() == 5.0);
        }

        SECTION("With RawWeatherData") {
            auto rawWeatherData = std::vector<RawWeatherDatum> {
                    {tm{.tm_mday = 3}, 1, 1.0},
                    {tm{.tm_mday = 3}, 3, 2.0},
                    {tm{.tm_mday = 2}, 1, 0.5},
                    {tm{.tm_mday = 3}, 1, 4.0},
                    {tm{.tm_mday = 5}, 1, 5.0}
            };

            REQUIRE(TimeSeries::MinValue<RawWeatherDatum>(rawWeatherData).getValue() == 0.5);
        }
    }

    SECTION("MaxValue") {
        SECTION("With TimeSeriesDataPoints") {
            auto timeSeriesData = std::vector<TimeSeriesDataPoint> {
                    {tm{.tm_mday = 3}, 100.0},
                    {tm{.tm_mday = 2}, 10.0},
                    {tm{.tm_mday = 3}, 30.0},
                    {tm{.tm_mday = 3}, 5.0},
                    {tm{.tm_mday = 0}, 5.1}
            };

            REQUIRE(TimeSeries::MaxValue<TimeSeriesDataPoint>(timeSeriesData).getValue() == 100.0);
        }

        SECTION("With RawWeatherData") {
            auto rawWeatherData = std::vector<RawWeatherDatum> {
                    {tm{.tm_mday = 3}, 1, 1.0},
                    {tm{.tm_mday = 3}, 3, 2.0},
                    {tm{.tm_mday = 2}, 1, 0.5},
                    {tm{.tm_mday = 3}, 1, 4.0},
                    {tm{.tm_mday = 5}, 1, 5.0}
            };

            REQUIRE(TimeSeries::MaxValue<RawWeatherDatum>(rawWeatherData).getValue() == 5.0);
        }
    }
}
