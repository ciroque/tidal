//
// Created by Steve Wagner on 9/20/20.
//

#ifndef TIDAL_APPLICATION_H
#define TIDAL_APPLICATION_H

#include <lunar.h>
#include <src/app/config/AppConfig.h>
#include "DisplayManager.h"
#include "LunarData.h"

class Application {
public:
    Application();
    ~Application();
    void Run();

private:
    bool stop{};
    const unsigned int ZERO_HOUR = 0;
    DisplayManager DisplayMgr;
    AppConfig config;

    LunarData GetLunarData();
    void HourlyUpdate();

    static void RegisterSignalHandlers();
    static void SignalHandler(int signum);
};

#endif //TIDAL_APPLICATION_H
