//
// Created by swagner on 8/14/21.
//

#ifndef TIDAL_APPCONFIG_H
#define TIDAL_APPCONFIG_H

#include "ConfigReader.h"

class AppConfig {
private:
    int lookAheadDays = -0;
    int tideNoaaStation = -0;
    std::string weatherNwsOffice;
    int weatherNwsGridX = -0;
    int weatherNwsGridY = -0;

public:
    [[nodiscard]] inline int getLookAheadDays() const { return lookAheadDays; }

    static AppConfig Load();
    static AppConfig Load(std::string path);
};

#endif //TIDAL_APPCONFIG_H
