//
// Created by swagner on 8/14/21.
//

#ifndef TIDAL_APPCONFIG_H
#define TIDAL_APPCONFIG_H

#include "ConfigReader.h"

class AppConfig {
private:
    int lookAheadDays = -0;

    std::string tideStation;
    std::string tideHttpPort;
    std::string tideHttpHost;
    std::string tideTimezone;
    std::string tideRootPath;

    std::string weatherNwsOffice;
    int weatherNwsGridX = -0;
    int weatherNwsGridY = -0;

public:
    [[nodiscard]] inline int getLookAheadDays() const { return lookAheadDays; }

    [[nodiscard]] inline std::string getTideStation() const { return tideStation; }
    [[nodiscard]] inline std::string getTideHttpPort() const { return tideHttpPort; }
    [[nodiscard]] inline std::string getTideHttpHost() const { return tideHttpHost; }
    [[nodiscard]] inline std::string getTideTimezone() const { return tideTimezone; }
    [[nodiscard]] inline std::string getTideRootPath() const { return tideRootPath; }

    static AppConfig Load();
    static AppConfig Load(std::string path);
};

#endif //TIDAL_APPCONFIG_H
