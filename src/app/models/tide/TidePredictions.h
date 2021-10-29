//
// Created by ciroque on 2021-10-21.
//

#ifndef TIDAL_TIDEPREDICTIONS_H
#define TIDAL_TIDEPREDICTIONS_H


#include <src/app/retrievers/TideRetriever.h>
#include <src/app/TimeSeriesDataPoint.h>
#include "TideData.h"

class TidePredictions {
private:
    TideRetriever retriever;
    std::vector<TimeSeriesDataPoint> predictions;

public:
    explicit TidePredictions(const TideRetriever &retriever);

    TidePredictions Load();
    TideData ForDate(const tm date);
    TimeSeriesDataPoint HighestTide();
    TimeSeriesDataPoint LowestTide();
};


#endif //TIDAL_TIDEPREDICTIONS_H
