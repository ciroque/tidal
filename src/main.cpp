#include "TidalConfig.h"
#include "app/Application.h"

#include <iostream>
#include <src/app/config/ConfigFileNotFoundException.h>

int main() {
    std::cout << "Tidal version " << tidal_VERSION_MAJOR << "." << tidal_VERSION_MINOR << std::endl;

    Application application;

    try {
        application.Run();

    } catch (ConfigFileNotFoundException& ex) {
        std::cout << "EXCEPTION: " << ex.what();
        return EXIT_FAILURE;

    } catch(std::runtime_error& error) {
        std::cerr << "EXCEPTION: " << error.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
