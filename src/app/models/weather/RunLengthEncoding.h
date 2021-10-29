//
// Created by ciroque on 2021-10-28.
//

#ifndef TIDAL_RUNLENGTHENCODING_H
#define TIDAL_RUNLENGTHENCODING_H


#include "RawWeatherDatum.h"

class RunLengthEncoding {
public:
    static std::vector<RawWeatherDatum> Decode(std::vector<RawWeatherDatum> data);
};


#endif //TIDAL_RUNLENGTHENCODING_H
