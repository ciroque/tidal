//
// Created by swagner on 10/3/20.
//

#include "DisplayManager.h"
#include "graphLib.h"
#include "DisplayData.h"

using namespace boost::adaptors;

void DisplayManager::LoadMoonImages() {
    fileNames.at(0) = "New.bmp";
    fileNames.at(1) = "WaxingCrescent.bmp";
    fileNames.at(2) = "FirstQuarter.bmp";
    fileNames.at(3) = "WaxingGibbous.bmp";
    fileNames.at(4) = "Full.bmp";
    fileNames.at(5) = "WaningGibbous.bmp";
    fileNames.at(6) = "LastQuarter.bmp";
    fileNames.at(7) = "WaningCrescent.bmp";

    /*Sprite Creation Start*/
    SDL_Init(SDL_INIT_EVERYTHING);
    for(const auto& fileName : fileNames | indexed()) {
        auto *bmp = SDL_LoadBMP(fileName.value().c_str());
        /*Copy pixel data to sprite buffer*/
        if(!bmp) {
            std::string error;
            error.append("Could not load image: ");
            error.append(fileName.value());
            throw std::runtime_error(error);
        }
        moonImages.at(fileName.index()) = FrameBufFromSurface(bmp);
        SDL_FreeSurface(bmp);
    }
    /*Sprite Creation End*/
}

frameBuf *DisplayManager::FrameBufFromSurface(SDL_Surface *img)
{
    SDL_LockSurface(img);
    auto *sprite = createBuffer(img->w, img->h, 32);
    for(int i = 0; i < (img->h * img->w); i++)
    {
        if(img->w != img->pitch)
        {
            ((Uint8 *)sprite->fb)[4 * i] =
                    ((Uint8 *)img->pixels)[img->pitch * i / img->w];
            ((Uint8 *)sprite->fb)[4 * i + 1] =
                    ((Uint8 *)img->pixels)[img->pitch * i / img->w + 1];
            ((Uint8 *)sprite->fb)[4 * i + 2] =
                    ((Uint8 *)img->pixels)[img->pitch * i / img->w + 2];
        }else{
            sprite->fb[i] = (unsigned int)((Uint8 *)img->pixels)[i];
            sprite->fb[i] |= (unsigned int)((Uint8 *)img->pixels)[i] << 8;
            sprite->fb[i] |= (unsigned int)((Uint8 *)img->pixels)[i] << 16;
        }
    }
    SDL_UnlockSurface(img);
    return sprite;
}

void DisplayManager::CopyBuffer()
{
    FILE *frameBuffer = fopen("/dev/fb0", "w");
    if(!frameBuffer)
        throw("Could not open frameBuffer");
    fwrite(buffer->fb, sizeof(int), buffer->size, frameBuffer);
    fclose(frameBuffer);
}

void DisplayManager::Render(DisplayData displayData) {
    LGL_cls(buffer);
    auto phaseCount = displayData.lunarData.moonPhases.size();
    int channelWidth = buffer->width / phaseCount;
    int channelOffset = channelWidth / 2;
    for(const auto& phase : displayData.lunarData.moonPhases | indexed()) {
        copyBitmap(buffer,
                   moonImages.at(phase.value().segment),
                   phase.index() * channelWidth + channelOffset - (moonImages.at(phase.value().segment)->width / 2),
                   0);
    }
    CopyBuffer();
}

DisplayManager::DisplayManager() = default;
