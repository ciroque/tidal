//
// Created by Steve Wagner on 9/20/20.
//

#ifndef TIDAL_APPLICATION_H
#define TIDAL_APPLICATION_H

#include <lunar.h>

class Application {
public:
    Application();
    ~Application();
    void Run();

private:
    int period = 7;
    static bool stop;

    static const unsigned int SECONDS_IN_DAY = 60 * 60 * 24;
    static const unsigned int SECONDS_IN_HOUR = 60 * 60;

    static void DailyUpdate();
    static void GetMoonPhases();
    static void HourlyUpdate();
    static void SignalHandler(int signum);
};


#endif //TIDAL_APPLICATION_H
