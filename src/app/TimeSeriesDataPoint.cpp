//
// Created by swagner on 8/8/21.
//

#include "TimeSeriesDataPoint.h"

TimeSeriesDataPoint::TimeSeriesDataPoint(const std::string& timestamp, float value) {
    // isolate usage of boost date classes to this class
    boost::gregorian::date d = boost::gregorian::from_string(timestamp);
    this->timestamp = d;
    this->value = value;
}
