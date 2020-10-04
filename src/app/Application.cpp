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

Application::Application() = default;

Application::~Application() = default;

void Application::Run() {
    RegisterSignalHandlers();

    Application::DisplayMgr.LoadMoonImages();

    std::thread hourly (HourlyUpdate);
    std::thread daily (DailyUpdate);

    hourly.join();
    daily.join();
}

void Application::RegisterSignalHandlers() {
    signal(SIGINT, SignalHandler);
    signal(SIGHUP, SignalHandler);
    signal(SIGKILL, SignalHandler);
}

DisplayManager Application::DisplayMgr;

void Application::DailyUpdate() {
    while(!stop) {
        std::cout << "DailyUpdate" << std::endl;
        sleep(Time::SecondsToNextDay());
    }
}

LunarData Application::GetLunarData() {
    LunarData lunarData;
    const int FIRST = 0;
    std::vector<Phase> phases;
    phases.push_back(Lunar::GetMoonPhase());
    for(int i = 1; i < DAYS; i++) {
        phases.push_back(Lunar::GetMoonPhase(phases.at(FIRST).julianDay + i));
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
        }

        Application::DisplayMgr.Render(displayData);

        sleep(Time::SecondsToNextHour());
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
