//
// Created by swagner on 10/15/23.
//

#include <vector>
#include <string>

namespace WeatherCommon {
    const static std::vector<std::string> PredictionKeys = {
            "maxTemperature",
            "minTemperature",
            "temperature",
            "apparentTemperature",
            "probabilityOfPrecipitation",
            "windSpeed",
            "windGust",
            "skyCover"
    };
}
