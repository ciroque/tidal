//
// Created by ciroque on 2021-10-21.
//

#ifndef TIDAL_LUNARPREDICTIONS_H
#define TIDAL_LUNARPREDICTIONS_H


#include <src/app/models/LunarData.h>
#include <src/app/retrievers/LunarRetriever.h>

class LunarPredictions {
private:
    LunarRetriever retriever;
    std::vector<LunarData> predictions;

public:
    explicit LunarPredictions(const LunarRetriever &retriever);

    LunarData at(int index);
    LunarPredictions Load();
};


#endif //TIDAL_LUNARPREDICTIONS_H
