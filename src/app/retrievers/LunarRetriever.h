//
// Created by swagner on 9/8/21.
//

#ifndef TIDAL_LUNARRETRIEVER_H
#define TIDAL_LUNARRETRIEVER_H

#include <src/app/models/lunar/LunarData.h>
#include <vector>
#include <src/app/config/AppConfig.h>

class LunarRetriever {
public:
    explicit LunarRetriever(AppConfig *config);
    std::vector<LunarData> Retrieve();

private:
    AppConfig *config;
};

#endif //TIDAL_LUNARRETRIEVER_H
