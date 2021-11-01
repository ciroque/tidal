//
// Created by ciroque on 2021-10-21.
//

#include <src/app/models/utils/TimeSeries.h>
#include "TidePredictions.h"
#include "TideDataParser.h"

TidePredictions::TidePredictions(const TideRetriever &retriever) : retriever(retriever) { }

TidePredictions TidePredictions::Load() {
    auto data = retriever.Retrieve();
    this->predictions = TideDataParser::Parse(data);
    return *this;
}

TideData TidePredictions::ForDate(const tm date) {
    auto tideLevels = TimeSeries::ValuesForDate(this->predictions, date);
    auto lowestLevel = TimeSeries::MinValue(tideLevels);
    auto highestLevel = TimeSeries::MaxValue(tideLevels);
    return { tideLevels, highestLevel, lowestLevel };
}

TimeSeriesDataPoint TidePredictions::HighestTide() {
    return TimeSeries::MaxValue(this->predictions);
}

TimeSeriesDataPoint TidePredictions::LowestTide() {
    return TimeSeries::MinValue(this->predictions);
}
