//
// Created by Steve Wagner on 9/20/20.
//

#ifndef TIDAL_APPLICATION_H
#define TIDAL_APPLICATION_H

#include <lunar.h>
#include "DisplayManager.h"
#include "LunarData.h"

class Application {
public:
    Application();
    ~Application();
    static void Run();

private:
    int period = 7;
    static bool stop;
    static const unsigned int ZERO_HOUR = 0;
    static const int DAYS = 7;
    static DisplayManager DisplayMgr;

    static void DailyUpdate();
    static LunarData GetLunarData();
    static void HourlyUpdate();
    static void SignalHandler(int signum);
    static void RegisterSignalHandlers() ;
};


#endif //TIDAL_APPLICATION_H
