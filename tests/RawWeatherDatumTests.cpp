//
// Created by ciroque on 2021-10-27.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include <utility>

#include "../src/app/models/weather/RawWeatherDatum.h"

int TestValue(const std::string& timestamp) {
    RawWeatherDatum datum = RawWeatherDatum::Build(timestamp, 0.0);
    return datum.GetRecurrence();
}

TEST_CASE("RawWeatherDatum") {
    SECTION("DetermineRecurrence") {
        REQUIRE(TestValue("2021-10-21T18:00:00+00:00/PT1H") == 1);
        REQUIRE(TestValue("2021-10-27T20:00:00+00:00/PT3H") == 3);
        REQUIRE(TestValue("2021-10-23T19:00:00+00:00/PT4H") == 4);
        REQUIRE(TestValue("2021-10-21T18:00:00+00:00") == 1);
        REQUIRE(TestValue("2021-10-23T19:00:00+00:00/PT4D") == 1);
    }

    SECTION("Build") {
        SECTION("Time is adjusted to local time") {
            auto baseTimestamp = "2021-10-30T12:00:00+00:00/PT1H";
            auto rwd = RawWeatherDatum::Build(baseTimestamp, 0.0);
            REQUIRE(rwd.GetTimestamp().tm_hour == 5);
        }

        SECTION("Time is adjusted to local time, previous day") {
            auto baseTimestamp = "2021-10-30T03:00:00+00:00/PT1H";
            auto rwd = RawWeatherDatum::Build(baseTimestamp, 0.0);
            REQUIRE(rwd.GetTimestamp().tm_hour == 20);
            REQUIRE(rwd.GetTimestamp().tm_mday == 29);
        }
    }
}
