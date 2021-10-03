#include "TidalConfig.h"
#include "app/Application.h"

#include <iostream>
#include <src/app/config/ConfigFileNotFoundException.h>

int main() {
    std::cout << "Tidal version " << tidal_VERSION_MAJOR << "." << tidal_VERSION_MINOR << std::endl;

    Application application;

    try {
        application.Run();

    } catch(std::exception& ex) {
        std::cout << "std::exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;

    } catch(...) {
        std::cout << "CATCH ALL THE THINGS:" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
