 //
// Created by ciroque on 2021-10-21.
//

#include "LunarPredictions.h"

LunarPredictions::LunarPredictions(const LunarRetriever &retriever) : retriever(retriever) { }

LunarData LunarPredictions::at(int index) {
    return predictions.at(index);
}

LunarPredictions LunarPredictions::Load() {
    this->predictions = retriever.Retrieve();
    return *this;
}
