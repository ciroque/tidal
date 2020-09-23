//
// Created by Steve Wagner on 9/20/20.
//

#include <iostream>
#include <thread>
#include <zconf.h>

#include "Application.h"
#include "Sleeper.h"

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
    while(!stop) {
        std::cout << "DailyUpdate: period: " << period << std::endl;
        GetMoonPhases();
        sleep(period);
        period = 60 * 60 * 24;
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
        period = 60 * 60;
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
