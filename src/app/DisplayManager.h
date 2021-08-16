//
// Created by swagner on 10/3/20.
//

#ifndef TIDAL_DISPLAYMANAGER_H
#define TIDAL_DISPLAYMANAGER_H

#include "graphLib.h"
#include "DisplayData.h"

#include <boost/range/adaptor/indexed.hpp>
#include <array>
#include <lunar.h>

//using namespace boost::adaptors;

class DisplayManager {
public:
    DisplayManager();
    void Render(DisplayData displayData);

private:
    frameBuf *buffer = createBuffer(1024, 768, 32);

    void DrawMoonPhase(float centerx, float centery, float radius, float phase);
    void CopyBuffer();
};

#endif //TIDAL_DISPLAYMANAGER_H
