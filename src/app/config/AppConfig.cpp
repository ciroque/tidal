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

    reader->getValue("tide.http-host", config.tideHttpHost);
    reader->getValue("tide.http-port", config.tideHttpPort);
    reader->getValue("tide.http-rootPath", config.tideHttpRootPath);
    reader->getValue("tide.station", config.tideStation);
    reader->getValue("tide.timezone", config.tideTimezone);

    reader->getValue("weather.http-host", config.weatherHttpHost);
    reader->getValue("weather.http-port", config.weatherHttpPort);
    reader->getValue("weather.http-rootPath", config.weatherHttpRootPath);
    reader->getValue("weather.office", config.weatherNwsOffice);
    reader->getValue("weather.gridX", config.weatherNwsGridX);
    reader->getValue("weather.gridY", config.weatherNwsGridY);

    return config;
}
