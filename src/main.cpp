#include "TidalConfig.h"
#include "app/Application.h"

#include <iostream>

int main() {
    std::cout << "Tidal version " << tidal_VERSION_MAJOR << "." << tidal_VERSION_MINOR << std::endl;

    try {
        Application::Run();
    } catch(std::runtime_error& error) {
        std::cerr << error.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
