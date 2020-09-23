//
// Created by Steve Wagner on 9/23/20.
//

#ifndef TIDAL_TIME_H
#define TIDAL_TIME_H

#include <ctime>

class Time {
private:
    static tm* GetLocalTime();
public:
    static unsigned int SecondsToNextHour();
    static unsigned int SecondsToNextDay();
    static unsigned int HoursNow();
};


#endif //TIDAL_TIME_H
