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
    time_t ttime = time(0);
    tm* local_time = localtime(&ttime);
    lunarData.moonPhases.push_back(Lunar::GetMoonPhase());
    char datestring[100];
    std::snprintf(datestring, sizeof(datestring), "%d/%d", local_time->tm_mon + 1, local_time->tm_mday);
    lunarData.moonDates.push_back(datestring);
    for(int i = 1; i < DAYS; i++) {
        lunarData.moonPhases.push_back(Lunar::GetMoonPhase(lunarData.moonPhases.at(FIRST).julianDay + i));
	local_time->tm_mday++;
	std::mktime(local_time);	/*Correct time if we go past the end of the month/year*/
	std::snprintf(datestring, sizeof(datestring), "%d/%d", local_time->tm_mon + 1, local_time->tm_mday);
	lunarData.moonDates.push_back(datestring);
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

            std::string tideData = tideRetriever.Retrieve(); // TODO: Grab the data and store it in the DisplayData class
            displayData.tideData = TideData::Parse(tideData);

//            std::string weatherData = weatherRetriever.Retrieve();  // TODO: Grab the data and store it in the DisplayData class
//            displayData.weatherData = WeatherData::Parse(weatherData);

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
