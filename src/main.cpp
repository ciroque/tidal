#include "TidalConfig.h"
#include "app/Application.h"

#include <lunar.h>

#include <iostream>
#include <zconf.h>

bool stop = false;

void signalHandler(int signum) {
    std::cout << "Received signal: " << signum << std::endl;
    if(signum == SIGTERM
        || signum == SIGINT
        || signum == SIGKILL) {
        stop = true;
    }
}

int main() {
    std::cout << "Tidal version " << tidal_VERSION_MAJOR << "." << tidal_VERSION_MINOR << std::endl;

    Application application;
    application.Run();

    signal(SIGINT, signalHandler);
    signal(SIGHUP, signalHandler);
    signal(SIGKILL, signalHandler);


    while(!stop) { sleep(1); }

    return 0;
}
