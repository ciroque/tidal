#include "TidalConfig.h"
#include "app/Application.h"

#include <iostream>

int main() {
    std::cout << "Tidal version " << tidal_VERSION_MAJOR << "." << tidal_VERSION_MINOR << std::endl;

    Application application;
    application.Run();

    return 0;
}
