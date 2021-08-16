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

    reader->getValue("tide.station", config.tideStation);
    reader->getValue("tide.http-port", config.tideHttpPort);
    reader->getValue("tide.http-host", config.tideHttpHost);
    reader->getValue("tide.timezone", config.tideTimezone);
    reader->getValue("tide.rootPath", config.tideRootPath);

    reader->getValue("weather.nws.office", config.weatherNwsOffice);
    reader->getValue("weather.nws.gridX", config.weatherNwsGridX);
    reader->getValue("weather.nws.gridY", config.weatherNwsGridY);

    return config;
}
