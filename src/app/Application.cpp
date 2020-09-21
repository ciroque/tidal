//
// Created by Steve Wagner on 9/20/20.
//

#include <iostream>
#include "Application.h"

void Application::Run() {
    std::cout << "Application is running" << std::endl;



}

Application::Application() {
    lunar = new Lunar();
}

Application::~Application() {
    delete lunar;
}
