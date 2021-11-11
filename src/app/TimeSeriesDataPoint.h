//
// Created by swagner on 8/8/21.
//

#ifndef TIDAL_TIMESERIESDATAPOINT_H
#define TIDAL_TIMESERIESDATAPOINT_H

#include <string>
#include <vector>

class TimeSeriesDataPoint {
private:
    static inline bool comparator(TimeSeriesDataPoint l, TimeSeriesDataPoint r) { return l.getValue() < r.getValue(); };

protected:
    tm timestamp{};
    double value;

public:
    TimeSeriesDataPoint();
    TimeSeriesDataPoint(tm timestamp, double);
    TimeSeriesDataPoint(const std::string&, double);

    [[nodiscard]] inline double getValue() const { return this->value; }
    [[nodiscard]] inline tm getTimestamp() const { return this->timestamp; }
};

#endif //TIDAL_TIMESERIESDATAPOINT_H
