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

    static void DailyUpdate();
    static void GetMoonPhases();
    static void HourlyUpdate();
    static void SignalHandler(int signum);
};


#endif //TIDAL_APPLICATION_H
