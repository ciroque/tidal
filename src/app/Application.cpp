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

    try {
        Application::_DisplayManager.LoadMoonImages();
    } catch(std::runtime_error error) {
        std::cerr << error.what();
        exit(1);
    }

    std::thread hourly (HourlyUpdate);
    std::thread daily (DailyUpdate);

    hourly.join();
    daily.join();
}

DisplayManager Application::_DisplayManager;

void Application::DailyUpdate() {
    TideRetriever tideRetriever;
    WeatherRetriever weatherRetriever;
    while(!stop) {
        std::cout << "DailyUpdate" << std::endl;
        auto phases = GetMoonPhases();
        Application::_DisplayManager.Render(phases);
        for(auto phase = phases.begin(); phase != phases.end(); phase++)
        {
            std::cout << phase->julianDay << ": " << Lunar::GetSegmentName(phase->segment) << " (" << phase->visible * 100 << "%)" << std::endl;
        }
        tideRetriever.Retrieve();
        weatherRetriever.Retrieve();
        sleep(Time::SecondsToNextDay());
    }
}

std::vector<Phase> Application::GetMoonPhases() {
    Lunar lunar;
    const int FIRST = 0;
    std::vector<Phase> phases;
    phases.push_back(lunar.GetMoonPhase());
    for(int i = 1; i < DAYS; i++) {
        phases.push_back(lunar.GetMoonPhase(phases.at(FIRST).julianDay + i));
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
