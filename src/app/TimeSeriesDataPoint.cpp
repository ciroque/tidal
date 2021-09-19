//
// Created by swagner on 8/8/21.
//

#include "TimeSeriesDataPoint.h"

TimeSeriesDataPoint::TimeSeriesDataPoint(const std::string& timestamp, float value) {
    strptime(timestamp.c_str(), "%Y-%m-%d %H:%M", &this->timestamp);
    this->value = value;
}

std::vector<TimeSeriesDataPoint> TimeSeriesDataPoint::ValuesForDate(std::vector<TimeSeriesDataPoint> vector, tm date) {
    auto predicate = [&date](const TimeSeriesDataPoint& tsdp) {
        return (tsdp.getTimestamp().tm_mon == date.tm_mon)
               && (tsdp.getTimestamp().tm_mday == date.tm_mday);
    };

    std::vector<TimeSeriesDataPoint> found;
    std::copy_if(vector.begin(), vector.end(), std::back_inserter(found), predicate);

    return found;
}
