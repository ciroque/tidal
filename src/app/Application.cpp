//
// Created by Steve Wagner on 9/20/20.
//

#include <iomanip>
#include <iostream>
#include <thread>
#include <zconf.h>
#include <csignal>
#include <src/app/translaters/DataManager.h>

#include "Application.h"
#include "Time.h"
#include "src/app/retrievers/LunarRetriever.h"
#include "src/app/retrievers/TideRetriever.h"
#include "src/app/retrievers/WeatherRetriever.h"
#include "src/app/models/DisplayData.h"

Application::Application() = default;

Application::~Application() = default;

void Application::Run() {
    LoadConfig();
    RegisterSignalHandlers();
    std::thread hourly (&Application::HourlyUpdate, this);
    hourly.join();
}

void Application::LoadConfig() {
    this->config = AppConfig::Load();
}

void Application::RegisterSignalHandlers() {
    signal(SIGTERM, SignalHandler);
    signal(SIGINT, SignalHandler);
    signal(SIGKILL, SignalHandler);
}

[[noreturn]] void Application::HourlyUpdate() {
    DisplayData displayData;
    LunarRetriever lunarRetriever(&config);
    TideRetriever tideRetriever(&config);
    WeatherRetriever weatherRetriever(&config);

    auto dataManager = DataManager(&config);
    while(true) {
        auto curhour = Time::HoursNow();
        std::cout << "HourlyUpdate: hour: " << curhour << std::endl;

        if(!displayData.loaded || curhour == ZERO_HOUR) {
	    displayData = dataManager.BuildDisplayData();
            displayData.loaded = true;
        }

	displayData.hour = curhour;

        Application::DisplayMgr.Render(displayData);

        unsigned int secondsToNextHour = Time::SecondsToNextHour();
        displaySecondsToNextUpdate(secondsToNextHour);
        sleep(secondsToNextHour);
    }
}

void Application::displaySecondsToNextUpdate(unsigned int secondsToNextHour) {
    auto lt = Time::GetLocalTime();
    std::cout
        << secondsToNextHour
        << " seconds from "
        << std::setfill('0')
        << std::setw(2)
        << lt.tm_hour
        << ":"
        << std::setfill('0')
        << std::setw(2)
        << lt.tm_min
        << ":"
        << std::setfill('0')
        << std::setw(2)
        << lt.tm_sec
        << std::endl;
}

void Application::SignalHandler(int signum) {
    std::cout << "Received signal: " << signum << std::endl;
    if(signum == SIGTERM
       || signum == SIGINT
       || signum == SIGKILL) {
        exit(signum);
    }
}
