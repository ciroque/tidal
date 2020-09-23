//
// Created by Steve Wagner on 9/20/20.
//

#include <iostream>
#include <thread>
#include <zconf.h>
#include <signal.h>

#include "Application.h"
#include "Sleeper.h"
#include "TideRetriever.h"
#include "WeatherRetriever.h"

bool Application::stop = false;

Application::Application() {
}

Application::~Application() {
}

void Application::Run() {
    signal(SIGINT, SignalHandler);
    signal(SIGHUP, SignalHandler);
    signal(SIGKILL, SignalHandler);

    std::thread hourly (HourlyUpdate);
    std::thread daily (DailyUpdate);

    hourly.join();
    daily.join();
}

void Application::DailyUpdate() {
    unsigned int period = Sleeper::SecondsToNextDay();
    TideRetriever tideRetriever;
    WeatherRetriever weatherRetriever;
    while(!stop) {
        std::cout << "DailyUpdate: period: " << period << std::endl;
        GetMoonPhases();
        tideRetriever.Retrieve();
        weatherRetriever.Retrieve();
        sleep(period);
        period = SECONDS_IN_DAY;
    }
}

void Application::GetMoonPhases() {
    Lunar lunar;
    const int DAYS = 7;
    std::array<Phase, DAYS> phases;
    phases.at(0) = lunar.GetMoonPhase();
    for(int i = 1; i < DAYS; i++) {
        phases.at(i) = lunar.GetMoonPhase(phases.at(0).julianDay + i);
    }

    for(auto it = phases.begin(); it != phases.end(); it++) {
        std::cout << it->julianDay << ": " << Lunar::GetSegmentName(it->segment) << " (" << it->visible * 100 << "%)" << std::endl;
    }
}

void Application::HourlyUpdate() {
    unsigned int period = Sleeper::SecondsToNextHour();
    while(!stop) {
        std::cout << "HourlyUpdate: period: " << period << std::endl;
        sleep(period);
        period = SECONDS_IN_HOUR;
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
