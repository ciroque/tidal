//
// Created by swagner on 8/14/21.
//

#ifndef TIDAL_WEATHERCONFIG_H
#define TIDAL_WEATHERCONFIG_H


#include <string>

class WeatherConfig {
private:
    std::string office = "wfo";
    int gridX = 119;
    int gridY = 76;

public:
    inline std::string getOffice() { return office; }
    [[nodiscard]] inline int getGridX() const { return gridX; }
    [[nodiscard]] inline int getGridY() const { return gridY; }
};

#endif //TIDAL_WEATHERCONFIG_H
