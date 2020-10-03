//
// Created by Steve Wagner on 9/20/20.
//

#include <iostream>
#include <thread>
#include <zconf.h>
#include <signal.h>

#include "Application.h"
#include "Time.h"
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
    TideRetriever tideRetriever;
    WeatherRetriever weatherRetriever;
    while(!stop) {
        std::cout << "DailyUpdate" << std::endl;
        auto phases = GetMoonPhases();
        for(auto phase = phases.begin(); phase != phases.end(); phase++)
        {
            std::cout << phase->julianDay << ": " << Lunar::GetSegmentName(phase->segment) << " (" << phase->visible * 100 << "%)" << std::endl;
        }
        tideRetriever.Retrieve();
        weatherRetriever.Retrieve();
        sleep(Time::SecondsToNextDay());
    }
}

std::array<Phase, Application::DAYS> Application::GetMoonPhases() {
    Lunar lunar;
    std::array<Phase, DAYS> phases;
    phases.at(0) = lunar.GetMoonPhase();
    for(int i = 1; i < DAYS; i++) {
        phases.at(i) = lunar.GetMoonPhase(phases.at(0).julianDay + i);
    }

    return phases;
}

void Application::HourlyUpdate() {
    while(!stop) {
        unsigned int hour = Time::HoursNow();
        std::cout << "HourlyUpdate: hour: " << hour << std::endl;
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
