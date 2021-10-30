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
    SECTION("Recurrence") {
        REQUIRE(TestValue("2021-10-21T18:00:00+00:00/PT1H") == 1);
        REQUIRE(TestValue("2021-10-27T20:00:00+00:00/PT3H") == 3);
        REQUIRE(TestValue("2021-10-23T19:00:00+00:00/PT4H") == 4);
        REQUIRE(TestValue("2021-10-21T18:00:00+00:00") == 1);
        REQUIRE(TestValue("2021-10-23T19:00:00+00:00/PT4D") == 1);
    }
}
