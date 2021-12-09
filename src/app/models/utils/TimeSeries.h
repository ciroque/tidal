//
// Created by ciroque on 2021-10-31.
//

#ifndef TIDAL_TIMESERIES_H
#define TIDAL_TIMESERIES_H

#include <vector>
#include "../../TimeSeriesDataPoint.h"

class TimeSeries {
private:
    static inline bool comparator(TimeSeriesDataPoint l, TimeSeriesDataPoint r) { return l.getValue() < r.getValue(); };

public:

    // NOTE: This definition must live in the header file, DO NOT MOVE IT TO THE SOURCE FILE.
    // @see https://stackoverflow.com/questions/14005060/undefined-reference-to/14005118#14005118
    //
    //      You have defined your template in a separate .cpp file.
    //      Each file is compiled separately.
    //      Your create.cpp doesn't contain any running code so it is being discarded by the compiler.
    //      Later, at a linkage stage, when the linker tries to link the binary of main.cpp with create_list,
    //      it can't find it in other compiled objects thus you are getting this error.
    //      To resolve it you need to instantiate your template at least once in your create.cpp
    //      or have the implementation inside the header file.
    template <typename T>
    static std::vector<T> ValuesForHour(std::vector<T> vector, int hour) {
        auto predicate = [&hour](const T& timeSeriesDataPoint) {
            return (timeSeriesDataPoint.getTimestamp().tm_hour == hour);
        };

        std::vector<T> found;
        std::copy_if(vector.begin(), vector.end(), std::back_inserter(found), predicate);

        return found;
    }

    template <typename T>
    static std::vector<T> ValuesForDate(std::vector<T> vector, tm date) {
        auto predicate = [&date](const T& tsdp) {
            return (tsdp.getTimestamp().tm_mon == date.tm_mon)
                   && (tsdp.getTimestamp().tm_mday == date.tm_mday);
        };

        std::vector<T> found;
        std::copy_if(vector.begin(), vector.end(), std::back_inserter(found), predicate);

        return found;
    }

    template<typename T>
    static T MinValue(const std::vector<T>& vector) {
        return *std::min_element(vector.begin(), vector.end(), comparator);
    }

    template<typename T>
    static T MaxValue(const std::vector<T>& vector) {
        return *std::max_element(vector.begin(), vector.end(), comparator);
    }

    template <typename T>
    static double AverageValue(const std::vector<T> vector) {
        if(vector.empty()) {
            return 0.0;
        }

        auto sum = 0.0;
        for(auto item : vector) {
            sum += item.getValue();
        }

        double average = sum / vector.size();
        return  average;
    }

};

#endif //TIDAL_TIMESERIES_H
