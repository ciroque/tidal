//
// Created by swagner on 10/3/20.
//

#include "DisplayManager.h"
#include "graphLib.h"
#include "DisplayData.h"
//#define XTESTING

using namespace boost::adaptors;

static inline float CircEquat(float rsqr, float x)
{
	return sqrt(rsqr - (x * x));
}

void DisplayManager::DrawMoonPhase(float centerx, float centery, float radius, float phase)
{
    radius *= SCALEFACTOR;
    float rsquared = radius * radius;
    float a = tan(phase) * radius;
    float b = sqrt(rsquared + (a * a));
    b *= b;
    float sign = (a >= 0) ? 1.0f : -1.0f;
    float side = fmod(phase, 2 * M_PI) > M_PI ? -1 : 1;
    for(int i = -radius; i < radius; i++){
        float edgex = CircEquat(rsquared, i) * side;
        float midx = CircEquat(b, i) * sign - a;
        drawline(superSample, SUPERAD + midx, SUPERAD + i, SUPERAD + edgex, SUPERAD + i, 0xE0E0E0);
    }
    scaleBitmap(normalSample, superSample);
    LGL_cls(superSample);
    copyBitmap(buffer, normalSample, centerx - MOONRAD, centery - MOONRAD);
}

void DisplayManager::CopyBuffer()
{
#ifdef XTESTING
    FILE *frameBuffer = fopen("/tmp/fb", "w");
#else
    FILE *frameBuffer = fopen("/dev/fb0", "w");
#endif
    if(!frameBuffer)
        throw("Could not open frameBuffer");
    fwrite(buffer->fb, sizeof(int), buffer->size, frameBuffer);
    fclose(frameBuffer);
}

void DisplayManager::Render(DisplayData displayData) {
    LGL_cls(buffer);
    static auto phaseCount = displayData.lunarData.moonPhases.size();
    static int channelWidth = buffer->width / phaseCount;
    static int halfChannelWidth = channelWidth / 2;
    static int channelOffset = channelWidth / 2;
    for(const auto& phase : displayData.lunarData.moonPhases | indexed()) {
	int xoffset = phase.index() * channelWidth + halfChannelWidth;
	if(phase.value().segment <= 4) DrawMoonPhase(xoffset, 90, 50, phase.value().visible * M_PI);
	else  DrawMoonPhase(xoffset, 90, 50, M_PI * 2 - phase.value().visible * M_PI);
	auto visString = std::to_string(phase.value().visible);
	int strOff = visString.length() * 5;	/*Pixel length of the string*/
	drawString(buffer, visString.c_str(), xoffset - strOff, 150, 0x0000FF);
	auto dateString = displayData.lunarData.moonDates.at(phase.index());
	strOff = dateString.length() * 10;	/*Getting date string*/
	drawBigString(buffer, dateString.c_str(), xoffset - strOff, 10, 0x0000FF);
	drawline(buffer, xoffset + halfChannelWidth, 0, xoffset + halfChannelWidth, 165, 0x0000FF);
    }
    drawline(buffer, 0, 165, buffer->width, 165, 0x0000FF);
    drawBigString(buffer, "Mystic Rhythms", 384, 384, 0xFF00FF);
    CopyBuffer();
}

DisplayManager::DisplayManager() = default;
