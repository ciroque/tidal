//
// Created by Steve Wagner on 9/20/20.
//

#include <iomanip>
#include <iostream>
#include <thread>
#include <zconf.h>
#include <csignal>

#include "Application.h"
#include "Time.h"
#include "src/app/retrievers/LunarRetriever.h"
#include "src/app/retrievers/TideRetriever.h"
#include "src/app/retrievers/WeatherRetriever.h"
#include "DisplayData.h"

Application::Application() {
    config = AppConfig::Load();
};

Application::~Application() = default;

void Application::Run() {
    RegisterSignalHandlers();
    std::thread hourly (&Application::HourlyUpdate, this);
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
    time_t ttime = time(0);
    tm* local_time = localtime(&ttime);
    lunarData.moonPhases.push_back(Lunar::GetMoonPhase());
    char datestring[100];
    std::snprintf(datestring, sizeof(datestring), "%d/%d", local_time->tm_mon + 1, local_time->tm_mday);
    lunarData.moonDates.push_back(datestring);
    for(int i = 1; i < config.getDaysToDisplay(); i++) {
        lunarData.moonPhases.push_back(Lunar::GetMoonPhase(lunarData.moonPhases.at(FIRST).julianDay + i));
	local_time->tm_mday++;
	std::mktime(local_time);	/*Correct time if we go past the end of the month/year*/
	std::snprintf(datestring, sizeof(datestring), "%d/%d", local_time->tm_mon + 1, local_time->tm_mday);
	lunarData.moonDates.push_back(datestring);
    }
    return lunarData;
}

[[noreturn]] void Application::HourlyUpdate() {
    DisplayData displayData;
    LunarRetriever lunarRetriever(&config);
    TideRetriever tideRetriever(&config);
    WeatherRetriever weatherRetriever(&config);

    while(true) {
        displayData.hour = Time::HoursNow();
        std::cout << "HourlyUpdate: hour: " << displayData.hour << std::endl;

        if(!displayData.loaded || displayData.hour == ZERO_HOUR) {

            // OLD AND BUSTED
            displayData.lunarData = GetLunarData();

            // THE NEW HOTNESS
            auto lunarData = lunarRetriever.Retrieve();

            std::string tideData = tideRetriever.Retrieve();
            displayData.tideData = TideData::Parse(tideData);

            std::string weatherData = weatherRetriever.Retrieve();
            displayData.weatherData = WeatherData::Parse(weatherData);

            displayData.loaded = true;
        }

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
        << lt->tm_hour
        << ":"
        << std::setfill('0')
        << std::setw(2)
        << lt->tm_min
        << ":"
        << std::setfill('0')
        << std::setw(2)
        << lt->tm_sec
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
