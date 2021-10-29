//
// Created by ciroque on 2021-10-28.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include <utility>
#include "../src/app/models/weather/RawWeatherDatum.h"
#include "../src/app/models/weather/RunLengthEncoding.h"

TEST_CASE("RunLengthEncoding") {
    SECTION("Decode") {
        SECTION("No recurrences") {
            tm timestamp { .tm_hour = 0, .tm_mday = 1, .tm_mon = 0, .tm_year = 220 };

            auto input = std::vector<RawWeatherDatum> {
                RawWeatherDatum(timestamp, 1, 0.0)
            };

            REQUIRE(RunLengthEncoding::Decode(input).size() == 1);
            REQUIRE(RunLengthEncoding::Decode(input).at(0).GetTimestamp().tm_hour == 0);
        }

        SECTION("Three recurrences") {
            tm timestamp { .tm_hour = 0, .tm_mday = 1, .tm_mon = 0, .tm_year = 220 };

            auto input = std::vector<RawWeatherDatum> {
                RawWeatherDatum(timestamp, 3, 0.0)
            };

            REQUIRE(RunLengthEncoding::Decode(input).size() == 3);
            REQUIRE(RunLengthEncoding::Decode(input).at(0).GetTimestamp().tm_hour == 0);
            REQUIRE(RunLengthEncoding::Decode(input).at(1).GetTimestamp().tm_hour == 1);
            REQUIRE(RunLengthEncoding::Decode(input).at(2).GetTimestamp().tm_hour == 2);
        }

        SECTION("Three recurrences cross midnight") {
            tm timestamp { .tm_hour = 22, .tm_mday = 1, .tm_mon = 0, .tm_year = 220 };

            auto input = std::vector<RawWeatherDatum> {
                RawWeatherDatum(timestamp, 3, 0.0)
            };

            REQUIRE(RunLengthEncoding::Decode(input).size() == 3);
            REQUIRE(RunLengthEncoding::Decode(input).at(0).GetTimestamp().tm_hour == 22);
            REQUIRE(RunLengthEncoding::Decode(input).at(1).GetTimestamp().tm_hour == 23);
            REQUIRE(RunLengthEncoding::Decode(input).at(2).GetTimestamp().tm_hour == 0);
            REQUIRE(RunLengthEncoding::Decode(input).at(2).GetTimestamp().tm_mday == 2
            );
        }

        SECTION("Multiple Datum") {
            tm timestamp1 { .tm_hour = 0, .tm_mday = 1, .tm_mon = 0, .tm_year = 220 };
            tm timestamp2 { .tm_hour = 3, .tm_mday = 1, .tm_mon = 0, .tm_year = 220 };

            auto input = std::vector<RawWeatherDatum> {
                RawWeatherDatum(timestamp1, 3, 10.0),
                RawWeatherDatum(timestamp2, 6, 20.0)
            };

            REQUIRE(RunLengthEncoding::Decode(input).size() == 9);
            REQUIRE(RunLengthEncoding::Decode(input).at(0).GetTimestamp().tm_hour == 0);
            REQUIRE(RunLengthEncoding::Decode(input).at(0).GetValue() == 10.0);

            REQUIRE(RunLengthEncoding::Decode(input).at(1).GetTimestamp().tm_hour == 1);
            REQUIRE(RunLengthEncoding::Decode(input).at(1).GetValue() == 10.0);

            REQUIRE(RunLengthEncoding::Decode(input).at(2).GetTimestamp().tm_hour == 2);
            REQUIRE(RunLengthEncoding::Decode(input).at(2).GetValue() == 10.0);

            REQUIRE(RunLengthEncoding::Decode(input).at(3).GetTimestamp().tm_hour == 3);
            REQUIRE(RunLengthEncoding::Decode(input).at(3).GetValue() == 20.0);

            REQUIRE(RunLengthEncoding::Decode(input).at(8).GetTimestamp().tm_hour == 8);
            REQUIRE(RunLengthEncoding::Decode(input).at(8).GetValue() == 20.0);
        }
    }
}