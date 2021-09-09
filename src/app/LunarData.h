//
// Created by swagner on 10/4/20.
//

#ifndef TIDAL_LUNARDATA_H
#define TIDAL_LUNARDATA_H

#include <vector>
#include <lunar.h>

class LunarData {
public:

    // OLD AND BUSTED
    LunarData();
    std::vector<Phase> moonPhases;
    std::vector<std::string> moonDates;

    // THE NEW HOTNESS
    explicit LunarData(Phase);

    int julianDay{};
    double sunPosition{};
    double moonPosition{};
    double visible{};
    Segment segment;
};


#endif //TIDAL_LUNARDATA_H
