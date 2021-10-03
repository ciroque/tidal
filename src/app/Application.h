//
// Created by Steve Wagner on 9/20/20.
//

#ifndef TIDAL_APPLICATION_H
#define TIDAL_APPLICATION_H

#include <lunar.h>
#include <src/app/config/AppConfig.h>
#include "DisplayManager.h"
#include "src/app/models/LunarData.h"

class Application {
public:
    Application();
    ~Application();
    void Run();
    void LoadConfig();

private:
    const unsigned int ZERO_HOUR = 0;
    DisplayManager DisplayMgr;
    AppConfig config;

    [[noreturn]] void HourlyUpdate();

    static void RegisterSignalHandlers();
    static void SignalHandler(int signum);

    static void DisplaySecondsToNextUpdate(unsigned int secondsToNextHour) ;

    static void LogHourlyUpdateToConsole(const DisplayData &displayData) ;
};

#endif //TIDAL_APPLICATION_H
