//
// Created by swagner on 8/14/21.
//

#ifndef TIDAL_APPCONFIG_H
#define TIDAL_APPCONFIG_H


#include "WeatherConfig.h"
#include "TideConfig.h"
#include "ConfigReader.h"

class AppConfig {
private:
    int lookAheadDays = 5;
    TideConfig tideConfig;
    WeatherConfig weatherConfig;

public:
    [[nodiscard]] inline int getLookAheadDays() const { return lookAheadDays; }
    inline WeatherConfig getWeatherConfig() { return weatherConfig; }
    inline TideConfig getTideConfig() { return tideConfig; }

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


        return config;
    }
};

#endif //TIDAL_APPCONFIG_H
