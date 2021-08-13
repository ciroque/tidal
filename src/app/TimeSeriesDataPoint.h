//
// Created by swagner on 8/8/21.
//

#ifndef TIDAL_TIMESERIESDATAPOINT_H
#define TIDAL_TIMESERIESDATAPOINT_H

#include <boost/date_time/gregorian/gregorian_types.hpp>        // DO NOT allow boost to expand beyond this class; this is our interface to boost
#include <boost/date_time/gregorian/parsers.hpp>

#include <string>

class TimeSeriesDataPoint {
private:
    boost::gregorian::date timestamp;
    float value;
public:
    TimeSeriesDataPoint(const std::string&, float);
    inline float getValue() const { return this->value; }
};

#endif //TIDAL_TIMESERIESDATAPOINT_H
