//
// Created by swagner on 8/8/21.
//

#include "TimeSeriesDataPoint.h"
#include "Time.h"

TimeSeriesDataPoint::TimeSeriesDataPoint() : TimeSeriesDataPoint(Time::GetLocalTime(), 0.0) { }

TimeSeriesDataPoint::TimeSeriesDataPoint(const tm timestamp, double value) {
    this->timestamp = timestamp;
    this->value = value;
}

TimeSeriesDataPoint::TimeSeriesDataPoint(const std::string& timestamp, double value) {
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

TimeSeriesDataPoint TimeSeriesDataPoint::MinValue(const std::vector<TimeSeriesDataPoint>& vector) {
    return *std::min_element(vector.begin(), vector.end(), comparator);
}

TimeSeriesDataPoint TimeSeriesDataPoint::MaxValue(const std::vector<TimeSeriesDataPoint>& vector) {
    return *std::max_element(vector.begin(), vector.end(), comparator);
}
