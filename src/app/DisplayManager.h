//
// Created by swagner on 10/3/20.
//

#ifndef TIDAL_DISPLAYMANAGER_H
#define TIDAL_DISPLAYMANAGER_H

#include "../graphLib/graphLib.h"

#include <boost/range/adaptor/indexed.hpp>
#include <SDL2/SDL.h>
#include <array>

//using namespace boost::adaptors;

class DisplayManager {
    static void Render();

private:
    static const int PHASECOUNT = 8;
    std::array<std::string, PHASECOUNT> fileNames;
    std::array<frameBuf*, PHASECOUNT> moonImages;

    void LoadMoonImages();
    frameBuf* FrameBufFromSurface(SDL_Surface *img);
    int copyBuffer(unsigned int *fb);
};


#endif //TIDAL_DISPLAYMANAGER_H
