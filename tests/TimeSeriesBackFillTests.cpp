////
//// Created by ciroque on 2021-11-02.
////
//
//#define CATCH_CONFIG_MAIN
//
//#include <catch2/catch_all.hpp>
//#include <utility>
//#include "../src/app/TimeSeriesDataPoint.h"
//#include "../src/app/models/utils/TimeSeries.h"
//
///*----------------------------------------------
// * This goes in the TimeSeriesBackFill class
// */
//template <typename T>
//std::vector<T> WithHourlyAverage(std::vector<T> vector) {
//    auto firstTimestamp = vector.at(0).getTimestamp();
//    auto hour = firstTimestamp.tm_hour - 1;
//
//    for( ; hour >= 0; hour--) {
//        auto hourValues = ValuesForHour(vector, hour);
//        auto average = TimeSeries::AverageValue(hourValues);
//        tm timestamp = firstTimestamp;
//        timestamp.tm_hour = hour;
//        vector.emplace(vector.begin(), TimeSeriesDataPoint(timestamp, average));
//    }
//
//    return vector;
//}
//
///*----------------------------------------------
// * This goes in the TimeSeries class (is actually part of https://github.com/ciroque/tidal/pull/46)
// */
//template <typename T>
//static std::vector<T> ValuesForHour(std::vector<T> vector, int hour) {
//    auto predicate = [&hour](const T& timeSeriesDataPoint) {
//        return (timeSeriesDataPoint.getTimestamp().tm_hour == hour);
//    };
//
//    std::vector<T> found;
//    std::copy_if(vector.begin(), vector.end(), std::back_inserter(found), predicate);
//
//    return found;
//}
//
//TEST_CASE("TimeSeriesBackFill") {
//    SECTION("WithHourlyAverage") {
//        auto timeSeries = std::vector<TimeSeriesDataPoint> {
//                {tm{.tm_hour = 3, .tm_mday = 3}, 0.0},
//                {tm{.tm_hour = 4, .tm_mday = 3}, 9.0},
//
//                {tm{.tm_hour = 0, .tm_mday = 4}, 1.0},
//                {tm{.tm_hour = 1, .tm_mday = 4}, 2.0},
//                {tm{.tm_hour = 2, .tm_mday = 4}, 3.0},
//                {tm{.tm_hour = 3, .tm_mday = 4}, 4.0},
//                {tm{.tm_hour = 4, .tm_mday = 4}, 9.0},
//
//                {tm{.tm_hour = 0, .tm_mday = 5}, 1.0},
//                {tm{.tm_hour = 1, .tm_mday = 5}, 2.0},
//                {tm{.tm_hour = 2, .tm_mday = 5}, 3.0},
//                {tm{.tm_hour = 3, .tm_mday = 5}, 4.0},
//                {tm{.tm_hour = 4, .tm_mday = 5}, 9.0},
//
//                {tm{.tm_hour = 0, .tm_mday = 6}, 1.0},
//                {tm{.tm_hour = 1, .tm_mday = 6}, 2.0},
//                {tm{.tm_hour = 2, .tm_mday = 6}, 3.0},
//                {tm{.tm_hour = 3, .tm_mday = 6}, 4.0},
//                {tm{.tm_hour = 4, .tm_mday = 6}, 9.0},
//
//                {tm{.tm_hour = 0, .tm_mday = 7}, 1.0},
//                {tm{.tm_hour = 1, .tm_mday = 7}, 2.0},
//                {tm{.tm_hour = 2, .tm_mday = 7}, 3.0},
//                {tm{.tm_hour = 3, .tm_mday = 7}, 4.0},
//                {tm{.tm_hour = 4, .tm_mday = 7}, 9.0}
//        };
//
//        REQUIRE(WithHourlyAverage(timeSeries).at(0).getTimestamp().tm_hour == 0);
//        REQUIRE(WithHourlyAverage(timeSeries).at(0).getValue() == 1.0);
//
//        REQUIRE(WithHourlyAverage(timeSeries).at(1).getTimestamp().tm_hour == 1);
//        REQUIRE(WithHourlyAverage(timeSeries).at(1).getValue() == 2.0);
//
//        REQUIRE(WithHourlyAverage(timeSeries).at(2).getTimestamp().tm_hour == 2);
//        REQUIRE(WithHourlyAverage(timeSeries).at(2).getValue() == 3.0);
//    }
//}
