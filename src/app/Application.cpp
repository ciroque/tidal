//
// Created by Steve Wagner on 9/20/20.
//

#include <iostream>
#include <thread>
#include <zconf.h>
#include <csignal>

#include "Application.h"
#include "Time.h"
#include "TideRetriever.h"
#include "WeatherRetriever.h"
#include "DisplayData.h"


bool Application::stop = false;

DisplayManager Application::DisplayMgr;

Application::Application() = default;

Application::~Application() = default;

void Application::Run() {
    RegisterSignalHandlers();
    Application::DisplayMgr.LoadMoonImages();
    std::thread hourly (HourlyUpdate);
    hourly.join();
}

void Application::RegisterSignalHandlers() {
    signal(SIGTERM, SignalHandler);
    signal(SIGINT, SignalHandler);
    signal(SIGKILL, SignalHandler);
}

LunarData Application::GetLunarData() {
    LunarData lunarData;
    const int FIRST = 0;
    lunarData.moonPhases.push_back(Lunar::GetMoonPhase());
    for(int i = 1; i < DAYS; i++) {
        lunarData.moonPhases.push_back(Lunar::GetMoonPhase(lunarData.moonPhases.at(FIRST).julianDay + i));
    }
    return lunarData;
}

void Application::HourlyUpdate() {
    DisplayData displayData;
    TideRetriever tideRetriever;
    WeatherRetriever weatherRetriever;
    while(!stop) {
        displayData.hour = Time::HoursNow();
        std::cout << "HourlyUpdate: hour: " << displayData.hour << std::endl;

        if(!displayData.loaded || displayData.hour == ZERO_HOUR) {
            displayData.lunarData = GetLunarData();
            tideRetriever.Retrieve(); // TODO: Grab the data and store it in the DisplayData class
            weatherRetriever.Retrieve();  // TODO: Grab the data and store it in the DisplayData class
            displayData.loaded = true;
        }

        Application::DisplayMgr.Render(displayData);

        unsigned int secondsToNextHour = Time::SecondsToNextHour();
        auto lt = Time::GetLocalTime();
        std::cout << secondsToNextHour << " seconds from " << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << std::endl;
        sleep(secondsToNextHour);
    }
}

void Application::SignalHandler(int signum) {
    std::cout << "Received signal: " << signum << std::endl;
    if(signum == SIGTERM
       || signum == SIGINT
       || signum == SIGKILL) {
        exit(signum);
    }
}
