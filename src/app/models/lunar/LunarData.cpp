//
// Created by swagner on 10/4/20.
//

#include "LunarData.h"

LunarData::LunarData() {
    this->julianDay = 0;
    this->phase = 0.0;
    this->segment = Segment::New;
    this->visible = 0;
}

LunarData::LunarData(Phase phase) {
    this->julianDay = phase.julianDay;
    this->phase = phase.phase;
    this->segment = phase.segment;
    this->visible = phase.visible;
}
