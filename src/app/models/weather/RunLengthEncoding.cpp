//
// Created by ciroque on 2021-10-28.
//

#include "RunLengthEncoding.h"

// Using the recurrence value, expand the number of data points appropriately.
// Note, this also converts the RawWeatherDatum to a TimeSeriesDataPoint.
std::vector<TimeSeriesDataPoint> RunLengthEncoding::Decode(std::vector<RawWeatherDatum> data) {
    std::vector<TimeSeriesDataPoint> decoded{};

    for(auto datum : data) {
        for(int index = 0; index < datum.GetRecurrence(); index++) {
            auto ts = datum.GetTimestamp();
            ts.tm_hour += index;
            std::mktime(&ts);

            decoded.emplace_back(ts, datum.GetValue());
        }
    }

    return decoded;
}
