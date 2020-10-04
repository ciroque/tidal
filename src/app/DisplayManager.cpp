//
// Created by swagner on 10/3/20.
//

#include "DisplayManager.h"

using namespace boost::adaptors;

void DisplayManager::Render() {

}

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
        auto *temp = SDL_LoadBMP(fileName.value().c_str());
        /*Copy pixel data to sprite buffer*/
        moonImages.at(fileName.index()) = FrameBufFromSurface(temp);
        SDL_FreeSurface(temp);
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
            sprite->fb[i] = (int)((Uint8 *)img->pixels)[i];
            sprite->fb[i] |= (int)((Uint8 *)img->pixels)[i] << 8;
            sprite->fb[i] |= (int)((Uint8 *)img->pixels)[i] << 16;
        }
    }
    SDL_UnlockSurface(img);
    return sprite;
}

int DisplayManager::copyBuffer(unsigned int *fb)
{
    FILE *thingey = fopen("/dev/fb0", "w");
    if(!thingey)
    {
        perror("Could not open thingey");
        return 1;
    }
    fwrite(fb, sizeof(int), SIZE, thingey);
    fclose(thingey);

    return 0;
}