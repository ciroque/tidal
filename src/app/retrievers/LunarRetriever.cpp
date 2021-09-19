//
// Created by swagner on 9/8/21.
//

#include "LunarRetriever.h"

LunarRetriever::LunarRetriever(AppConfig *config) {
    this->config = config;
}

std::vector<LunarData> LunarRetriever::Retrieve() {
    auto data = std::vector<LunarData>();

    auto firstMoonPhase = LunarData(Lunar::GetMoonPhase());
    data.push_back(firstMoonPhase);

    for(int i = 1; i < config->getDaysToDisplay(); i++) {
        int nextJulianDay = firstMoonPhase.julianDay + i;
        auto nextMoonPhase = LunarData(Lunar::GetMoonPhase(nextJulianDay));
        data.push_back(nextMoonPhase);
    }

    return data;
}
