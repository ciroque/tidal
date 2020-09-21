#include "TidalConfig.h"
#include "app/Application.h"

#include <lunar.h>

#include <iostream>

void signalHandler(int signum) {
    std::cout << "Received signal: " << signum << std::endl;
    exit(signum);
}

int main() {
    std::cout << "Tidal version " << tidal_VERSION_MAJOR << "." << tidal_VERSION_MINOR << std::endl;

    Application application;
    application.Run();

    signal(SIGINT, signalHandler);
    signal(SIGHUP, signalHandler);


    while(true) {;}
}
