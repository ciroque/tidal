//
// Created by wagnerdev on 9/19/21.
//

#ifndef TIDAL_PREDICTIONS_H
#define TIDAL_PREDICTIONS_H


#include <src/app/config/AppConfig.h>
#include <src/app/models/DisplayData.h>
#include "src/app/models/lunar/LunarPredictions.h"

class Predictions {
private:
    AppConfig *config;

public:
    explicit Predictions(AppConfig *config);
    DisplayData BuildDisplayData();
};

#endif //TIDAL_PREDICTIONS_H
