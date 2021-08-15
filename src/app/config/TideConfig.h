//
// Created by swagner on 8/14/21.
//

#ifndef TIDAL_TIDECONFIG_H
#define TIDAL_TIDECONFIG_H


class TideConfig {
private:
    int station = 9447130;
public:
    [[nodiscard]] inline int getStation() const { return station; }
};

#endif //TIDAL_TIDECONFIG_H
