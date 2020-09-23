//
// Created by Steve Wagner on 9/20/20.
//

#include <iostream>
#include <thread>
#include <zconf.h>

#include "Application.h"

Application::Application() {
}

Application::~Application() {
}

bool Application::stop = false;

void Application::Run() {
    signal(SIGINT, signalHandler);
    signal(SIGHUP, signalHandler);
    signal(SIGKILL, signalHandler);

    std::thread hourly (HourlyUpdate);
    std::thread daily (DailyUpdate);

    hourly.join();
    daily.join();
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

void Application::signalHandler(int signum) {
    std::cout << "Received signal: " << signum << std::endl;
    if(signum == SIGTERM
       || signum == SIGINT
       || signum == SIGKILL) {
        exit(signum);
    }
}

void Application::HourlyUpdate() {
    while(!stop) {
        std::cout << "HourlyUpdate" << std::endl;
        sleep(1);
    }
}

void Application::DailyUpdate() {
    while(!stop) {
        std::cout << "DailyUpdate" << std::endl;
        GetMoonPhases();
        sleep(24);
    }
}
