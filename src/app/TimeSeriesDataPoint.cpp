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
