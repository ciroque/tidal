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
    auto dataManager = DataManager(&config);
    while(true) {
        auto displayData = dataManager.BuildDisplayData();
        LogHourlyUpdateToConsole(displayData);

        Application::DisplayMgr.Render(displayData);

        unsigned int secondsToNextHour = Time::SecondsToNextHour();
        DisplaySecondsToNextUpdate(secondsToNextHour);
        sleep(secondsToNextHour);
    }
}

void Application::LogHourlyUpdateToConsole(const DisplayData &displayData) {
    std::cout << "HourlyUpdate: hour: " << displayData.hour << std::endl;
}

void Application::DisplaySecondsToNextUpdate(unsigned int secondsToNextHour) {
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
