//
// Created by swagner on 8/8/21.
//

#ifndef TIDAL_TIMESERIESDATAPOINT_H
#define TIDAL_TIMESERIESDATAPOINT_H

#include <string>
#include <vector>

class TimeSeriesDataPoint {
private:
    tm timestamp;
    float value;

public:
    TimeSeriesDataPoint(const std::string&, float);

    [[nodiscard]] inline float getValue() const { return this->value; }
    [[nodiscard]] inline tm getTimestamp() const { return this->timestamp; }

    static std::vector<TimeSeriesDataPoint> ValuesForDate(std::vector<TimeSeriesDataPoint> vector, tm date);
};

#endif //TIDAL_TIMESERIESDATAPOINT_H
