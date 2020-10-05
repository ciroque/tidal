//
// Created by Steve Wagner on 9/23/20.
//

#include "Time.h"

#include <ctime>

unsigned int Time::SecondsToNextHour() {
    tm* localTime = GetLocalTime();
    unsigned int minutes = 60 - localTime->tm_min;
    unsigned int seconds = 60 - localTime->tm_sec;
    return ((minutes - 1) * 60) + seconds;
}

unsigned int Time::HoursNow() {
    tm* localTime = GetLocalTime();
    return localTime->tm_hour;
}

tm *Time::GetLocalTime() {
    time_t ttime = time(0);
    tm* local_time = localtime(&ttime);
    return local_time;
}
