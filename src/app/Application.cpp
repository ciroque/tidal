//
// Created by Steve Wagner on 9/20/20.
//

#include <iostream>
#include "Application.h"

void Application::Run() {
    std::cout << "Application is running" << std::endl;
    const int DAYS = 30;
    std::array<Phase, DAYS> phases;
    phases.at(0) = lunar->GetMoonPhase();
    for(int i = 1; i < DAYS; i++) {
        phases.at(i) = lunar->GetMoonPhase(phases.at(0).julianDay + i);
    }

    for(auto it = phases.begin(); it != phases.end(); it++) {
        std::cout << it->julianDay << ": " << Lunar::GetSegmentName(it->segment) << " (" << it->visible * 100 << "%)" << std::endl;
    }
}

Application::Application() {
    lunar = new Lunar();
}

Application::~Application() {
    delete lunar;
}
