//
// Created by Steve Wagner on 9/20/20.
//

#ifndef TIDAL_APPLICATION_H
#define TIDAL_APPLICATION_H

#include <lunar.h>
#include "DisplayManager.h"

class Application {
public:
    Application();
    ~Application();
    void Run();

private:
    int period = 7;
    static bool stop;
    const static int DAYS = 7;

    static DisplayManager _DisplayManager;

    static void DailyUpdate();
    static std::vector<Phase> GetMoonPhases();
    static void HourlyUpdate();
    static void SignalHandler(int signum);
};


#endif //TIDAL_APPLICATION_H
