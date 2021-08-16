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
    std::string weatherNwsOffice = "";
    int weatherNwsGridX = -0;
    int weatherNwsGridY = -0;

public:
    [[nodiscard]] inline int getLookAheadDays() const { return lookAheadDays; }

    static AppConfig Load()
    {
        return Load("tidal.config");
    }

    static AppConfig Load(std::string path)
    {
        auto config = AppConfig();
        auto reader = ConfigReader::getInstance();

        reader->parseFile(path);

        reader->getValue("lookAheadDays", config.lookAheadDays);
        reader->getValue("tide.noaa.station", config.tideNoaaStation);
        reader->getValue("weather.nws.office", config.weatherNwsOffice);
        reader->getValue("weather.nws.gridX", config.weatherNwsGridX);
        reader->getValue("weather.nws.gridY", config.weatherNwsGridY);

        return config;
    }
};

#endif //TIDAL_APPCONFIG_H
