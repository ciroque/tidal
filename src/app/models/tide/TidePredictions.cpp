//
// Created by ciroque on 2021-10-21.
//

#include "TidePredictions.h"
#include "TideDataParser.h"

TidePredictions::TidePredictions(const TideRetriever &retriever) : retriever(retriever) { }

TidePredictions TidePredictions::Load() {
    auto data = retriever.Retrieve();
    this->predictions = TideDataParser::Parse(data);
    return *this;
}

TideData TidePredictions::ForDate(const tm date) {
    auto tideLevels = TimeSeriesDataPoint::ValuesForDate(this->predictions, date);
    auto lowestLevel = TimeSeriesDataPoint::MinValue(tideLevels);
    auto highestLevel = TimeSeriesDataPoint::MaxValue(tideLevels);
    return { tideLevels, highestLevel, lowestLevel };
}

TimeSeriesDataPoint TidePredictions::HighestTide() {
    return TimeSeriesDataPoint::MaxValue(this->predictions);
}

TimeSeriesDataPoint TidePredictions::LowestTide() {
    return TimeSeriesDataPoint::MinValue(this->predictions);
}
