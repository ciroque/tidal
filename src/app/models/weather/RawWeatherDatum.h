//#include <utility>

// Created by ciroque on 2021-10-21.
//

#ifndef TIDAL_RAWWEATHERDATUM_H
#define TIDAL_RAWWEATHERDATUM_H

#include <regex>
#include <string>

class RawWeatherDatum {
private:
    static const char DURATION_DELIMITER = '/';
    static const std::regex FULL_TIMESTAMP_PARSER;

    tm timestamp{};
    int recurrence;
    double value;

    RawWeatherDatum(tm timestamp, int recurrence, double value);

    static int Recurrence(const std::string& timestamp);

public:

    static RawWeatherDatum Build(const std::string& validTime, double value);

    [[nodiscard]] inline int GetRecurrence() const { return this->recurrence; }
    [[nodiscard]] inline tm GetTimestamp() const { return this->timestamp; };
    [[nodiscard]] inline double GetValue() const { return this->value; };
};


#endif //TIDAL_RAWWEATHERDATUM_H
