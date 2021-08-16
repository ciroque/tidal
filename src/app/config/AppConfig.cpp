//
// Created by swagner on 8/14/21.
//

#include "AppConfig.h"

AppConfig AppConfig::Load()
{
    return Load("tidal.config");
}

AppConfig AppConfig::Load(std::string path)
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
