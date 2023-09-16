//
// Created by swagner on 10/3/20.
//

#ifndef TIDAL_DISPLAYMANAGER_H
#define TIDAL_DISPLAYMANAGER_H

#include "graphLib.h"
#include "src/app/models/DisplayData.h"

#include <boost/range/adaptor/indexed.hpp>
#include <array>
#include <src/app/lunar/lunar.h>

#define MOONRAD 50
#define MOONDIA 2 * MOONRAD
#define SCALEFACTOR 10
#define SUPERAD MOONRAD * SCALEFACTOR

//using namespace boost::adaptors;

class DisplayManager {
public:
    DisplayManager();
    void Render(DisplayData displayData);

private:
    frameBuf *buffer = createBuffer(1024, 768, 32);
    frameBuf *superSample = createBuffer(MOONDIA * SCALEFACTOR, MOONDIA * SCALEFACTOR, 32);
    frameBuf *normalSample = createBuffer(MOONDIA, MOONDIA, 32);

    void DrawMoonPhase(float centerx, float centery, float radius, float phase);
    void CopyBuffer();
};

#endif //TIDAL_DISPLAYMANAGER_H
