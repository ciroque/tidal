//
// Created by swagner on 8/14/21.
//

#ifndef TIDAL_APPCONFIG_H
#define TIDAL_APPCONFIG_H

#include "ConfigReader.h"

class AppConfig {
private:
    int lookAheadDays = -0;

    std::string tideHttpPort;
    std::string tideHttpHost;
    std::string tideHttpRootPath;
    std::string tideStation;
    std::string tideTimezone;

    std::string weatherHttpHost;
    std::string weatherHttpPort;
    std::string weatherHttpRootPath;
    std::string weatherNwsOffice;
    std::string weatherNwsGridX;
    std::string weatherNwsGridY;

public:
    [[nodiscard]] inline int getLookAheadDays() const { return lookAheadDays; }

    [[nodiscard]] inline std::string getTideHttpHost() const { return tideHttpHost; }
    [[nodiscard]] inline std::string getTideHttpPort() const { return tideHttpPort; }
    [[nodiscard]] inline std::string getTideHttpRootPath() const { return tideHttpRootPath; }
    [[nodiscard]] inline std::string getTideStation() const { return tideStation; }
    [[nodiscard]] inline std::string getTideTimezone() const { return tideTimezone; }

    [[nodiscard]] inline std::string getWeatherHttpHost() const { return weatherHttpHost; }
    [[nodiscard]] inline std::string getWeatherHttpPort() const { return weatherHttpPort; }
    [[nodiscard]] inline std::string getWeatherHttpRootPath() const { return weatherHttpRootPath; }
    [[nodiscard]] inline std::string getWeatherOffice() const { return weatherNwsOffice; }
    [[nodiscard]] inline std::string getWeatherGridX() const { return weatherNwsGridX; }
    [[nodiscard]] inline std::string getWeatherGridY() const { return weatherNwsGridY; }

    static AppConfig Load();
    static AppConfig Load(std::string path);
};

#endif //TIDAL_APPCONFIG_H
