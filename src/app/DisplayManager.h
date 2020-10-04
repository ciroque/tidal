//
// Created by swagner on 10/3/20.
//

#ifndef TIDAL_DISPLAYMANAGER_H
#define TIDAL_DISPLAYMANAGER_H

#include "../graphLib/graphLib.h"

#include <boost/range/adaptor/indexed.hpp>
#include <SDL2/SDL.h>
#include <array>
#include <lunar.h>

//using namespace boost::adaptors;

class DisplayManager {
public:
    DisplayManager();
    void Render(std::vector<Phase> moonPhases);
    void LoadMoonImages();

private:
    static const int PHASECOUNT = 8;
    std::array<std::string, PHASECOUNT> fileNames;
    std::array<frameBuf*, PHASECOUNT> moonImages{};
    frameBuf *buffer = createBuffer(1024, 768, 32);

    static frameBuf* FrameBufFromSurface(SDL_Surface *img);
    void CopyBuffer();
};


#endif //TIDAL_DISPLAYMANAGER_H
