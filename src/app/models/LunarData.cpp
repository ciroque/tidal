//
// Created by swagner on 10/4/20.
//

#include "LunarData.h"

// OLD AND BUSTED
LunarData::LunarData() {
    this->julianDay = 0;
    this->moonPosition = 0;
    this->segment = Segment::New;
    this->sunPosition = 0;
    this->visible = 0;
}

// THE NEW HOTNESS
LunarData::LunarData(Phase phase) {
    this->julianDay = phase.julianDay;
    this->moonPosition = phase.moonPosition;
    this->segment = phase.segment;
    this->sunPosition = phase.sunPosition;
    this->visible = phase.visible;
}
