//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_LUNARDATA_H
#define TIDAL_LUNARDATA_H

#include <vector>
#include <src/app/lunar/lunar.h>

class LunarData {
public:
    LunarData();
    explicit LunarData(Phase);

    int julianDay{};
    double phase{};
    Segment segment;
    double visible{};
};


#endif //TIDAL_LUNARDATA_H
