//
// Created by swagner on 8/8/21.
//

#ifndef TIDAL_TIMESERIESDATAPOINT_H
#define TIDAL_TIMESERIESDATAPOINT_H

#include <string>
#include <vector>

class TimeSeriesDataPoint {
private:
    tm timestamp{};
    double value;

    static inline bool comparator(TimeSeriesDataPoint l, TimeSeriesDataPoint r) { return l.getValue() < r.getValue(); };

public:
    TimeSeriesDataPoint();
    TimeSeriesDataPoint(tm timestamp, double);
    TimeSeriesDataPoint(const std::string&, double);

    [[nodiscard]] inline float getValue() const { return this->value; }
    [[nodiscard]] inline tm getTimestamp() const { return this->timestamp; }

    static std::vector<TimeSeriesDataPoint> ValuesForDate(std::vector<TimeSeriesDataPoint> vector, tm date);
    static TimeSeriesDataPoint MinValue(const std::vector<TimeSeriesDataPoint>& vector);
    static TimeSeriesDataPoint MaxValue(const std::vector<TimeSeriesDataPoint>& vector);
};

#endif //TIDAL_TIMESERIESDATAPOINT_H
