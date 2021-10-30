//
// Created by ciroque on 2021-10-28.
//

#include "RunLengthEncoding.h"

std::vector<RawWeatherDatum> RunLengthEncoding::Decode(std::vector<RawWeatherDatum> data) {
    std::vector<RawWeatherDatum> decoded{};

    for(auto datum : data) {
        for(int index = 0; index < datum.GetRecurrence(); index++) {
            auto ts = datum.GetTimestamp();
            ts.tm_hour += index;
            std::mktime(&ts);

            decoded.emplace_back(ts, 1, datum.GetValue());
        }
    }

    return decoded;
}
