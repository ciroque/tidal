//
// Created by Steve Wagner on 9/23/20.
//

#include "Sleeper.h"

#include <ctime>

unsigned int Sleeper::SecondsToNextHour() {
    time_t ttime = time(0);
    tm* local_time = localtime(&ttime);
    unsigned int minutes = 60 - local_time->tm_min;
    unsigned int seconds = 60 - local_time->tm_sec;
    return (minutes * 60) + seconds;
}

unsigned int Sleeper::SecondsToNextDay() {
    time_t ttime = time(0);
    tm* local_time = localtime(&ttime);
    unsigned int hours = 24 - local_time->tm_hour;
    unsigned int minutes = 60 - local_time->tm_min;
    unsigned int seconds = 60 - local_time->tm_sec;
    return (hours * 60 * 60) + (minutes * 60) + seconds;
}
